// Fill out your copyright notice in the Description page of Project Settings.

#include "SW_Magic.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

ASW_Magic::ASW_Magic()
{
    // 기본적으로 투사체처럼 발사되지만, 마법 투사체는 추가 효과를 가짐.
    bTeleported = false;
    bUltimateTriggered = false;
    TeleportLifeDuration = 5.f; // 텔레포트 활성 후 5초 동안 그 자리에 머무름

    // 마법 투사체 전용으로 이동 속도 조정 (필요에 따라 수정)
    MoveSpeed = 1500.f;
}

void ASW_Magic::BeginPlay()
{
    Super::BeginPlay();
    // 필요하다면 BeginPlay에서 추가 설정 실행
}

void ASW_Magic::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // 텔레포트나 궁극 효과가 아직 활성화되지 않았다면, 부모의 이동 로직(직선 이동)을 사용.
    // 텔레포트 후 MoveSpeed를 0으로 설정했으므로 그 이후에는 이동하지 않게 됩니다.
}

//
// 여기서 OnOverlapBegin을 재정의하여
// 다른 캐릭터에 닿아도 투사체가 Destroy() 되지 않도록 합니다.
//
void ASW_Magic::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                               UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                               bool bFromSweep, const FHitResult& SweepResult)
{
    if (!HasAuthority()) return;

    // 자기 자신이나 Null 객체와의 충돌은 무시
    if (!OtherActor || OtherActor == this)
    {
        return;
    }

    // 원래 SW_ThrowActor에서는 충돌 시 데미지를 주고 Destroy()했지만,
    // 마법 투사체는 다른 캐릭터와 충돌해도 사라지지 않으므로 Destroy() 호출을 하지 않습니다.
    UGameplayStatics::ApplyDamage(OtherActor, Damage, GetInstigatorController(), this, UDamageType::StaticClass());
    // 여기서는 단순히 데미지만 적용하고, 투사체는 계속 남아 있게 됩니다.
}

void ASW_Magic::OnTeleportActivated()
{
    if (!bTeleported)
    {
        bTeleported = true;
        // 텔레포트 후에는 더 이상 이동하지 않도록 함
        MoveSpeed = 0.f;

        // 텔레포트 활성 후 일정 시간(TeleportLifeDuration) 후 자동 소멸되도록 타이머 설정
        GetWorldTimerManager().SetTimer(TeleportLifeTimerHandle, this, &ASW_Magic::DestroySelf, TeleportLifeDuration, false);
    }
}

void ASW_Magic::DestroySelf()
{
    Destroy();
}

void ASW_Magic::TriggerUltimate()
{
    if (!bUltimateTriggered && bTeleported)
    {
        bUltimateTriggered = true;
        // 자동 소멸 타이머 취소
        GetWorldTimerManager().ClearTimer(TeleportLifeTimerHandle);

        // 궁극 효과 시작: 투사체가 위로 떠오르게 합니다.
        FVector CurrentLocation = GetActorLocation();
        CurrentLocation.Z += 300.f; // 300 유닛 만큼 상승 (필요에 따라 조정)
        SetActorLocation(CurrentLocation);

        // 잠시 후 궁극 효과 낙하(땅에 내려꽂힘)를 실행하도록 타이머 설정
        FTimerHandle UltimateDescentTimerHandle;
        GetWorldTimerManager().SetTimer(UltimateDescentTimerHandle, this, &ASW_Magic::OnUltimateImpact, 0.5f, false);
    }
}

void ASW_Magic::OnUltimateImpact() 
{
    // 낙하 효과: 상승한 만큼 현재 위치에서 내려오기
    FVector ImpactLocation = GetActorLocation();
    ImpactLocation.Z -= 300.f; // 상승분 만큼 내림 (세부 값은 조정 가능)
    SetActorLocation(ImpactLocation);

    // 폭발 효과: 주변 액터에게 Radial Damage 적용
    float ExplosionRadius = 200.f; // 폭발 범위 (필요에 따라 조절)
    UGameplayStatics::ApplyRadialDamage(this, Damage, ImpactLocation, ExplosionRadius,
        UDamageType::StaticClass(), TArray<AActor*>(), this, GetInstigatorController(), true);

    // 궁극 효과 처리 완료 후 투사체 제거
    Destroy();
}
