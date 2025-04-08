#include "SW_Brall.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DamageEvents.h"
#include "InputActionValue.h"

ASW_Brall::ASW_Brall()
{
    // 대시 충돌 용 몸 전체 박스 콜리전 생성
    DashCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("DashCollider"));
    DashCollider->SetupAttachment(RootComponent);
    DashCollider->SetBoxExtent(FVector(150.f, 150.f, 100.f)); // X: 앞뒤, Y: 좌우, Z: 높이
    DashCollider->SetRelativeLocation(FVector(120.f, 0.f, 0.f)); // 앞쪽으로 밀기
    DashCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    DashCollider->SetCollisionResponseToAllChannels(ECR_Ignore);
    DashCollider->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
    DashCollider->OnComponentBeginOverlap.AddDynamic(this, &ASW_Brall::OnDashBoxOverlap);
    DashCollider->SetHiddenInGame(false); // 디버그용
    DashCollider->SetVisibility(true); // 디버그용

    static ConstructorHelpers::FObjectFinder<UAnimMontage> Combo1(TEXT("/Game/Characters/Brall/Animation/ComboAttack/AM_Brall_Combo1.AM_Brall_Combo1"));
    static ConstructorHelpers::FObjectFinder<UAnimMontage> Combo2(TEXT("/Game/Characters/Brall/Animation/ComboAttack/AM_Brall_Combo2.AM_Brall_Combo2"));
    static ConstructorHelpers::FObjectFinder<UAnimMontage> Combo3(TEXT("/Game/Characters/Brall/Animation/ComboAttack/AM_Brall_Combo3.AM_Brall_Combo3"));

    if (Combo1.Succeeded()) ComboMontages.Add(Combo1.Object);
    if (Combo2.Succeeded()) ComboMontages.Add(Combo2.Object);
    if (Combo3.Succeeded()) ComboMontages.Add(Combo3.Object);
    
    // 체력
    MaxHealth = 500;
    Health = MaxHealth;

    // 기본 스킬 설정
    FSkillData NormalSkillData;
    NormalSkillData.Damage = 20.f;
    NormalSkillData.AttackType = ESkillAttackType::BoxTrace;
    NormalSkillData.Range = FVector(600.f, 200.f, 300.f); // X: 길이, Y: 폭, Z: 높이
    NormalSkillData.Offset = FVector(300.f, 0.f, 0.f);
    SkillDataMap.Add(FName("NormalSkill"), NormalSkillData);

    // 스페셜 스킬 설정
    FSkillData SpecialSkillData;
    SpecialSkillData.Damage = 55.f;
    SpecialSkillData.AttackType = ESkillAttackType::MeleeBox; // Box
    SpecialSkillData.Range = FVector(300.f, 300.f, 200.f);  
    SpecialSkillData.Offset = FVector(200.f, 0.f, 0.f);        // 살짝 앞쪽으로
    SkillDataMap.Add(FName("SpecialSkill"), SpecialSkillData);

}

void ASW_Brall::BeginPlay()
{
    Super::BeginPlay();

    TArray<UChildActorComponent*> ChildActorComps;
    GetComponents<UChildActorComponent>(ChildActorComps);

    for (auto* Comp : ChildActorComps)
    {
        if (Comp && Comp->GetName().Contains("BrallSword"))
        {
            Sword = Comp;
            break;
        }
    }

    if (!Sword)
    {
        return;
    }

    if (!Sword->GetChildActor())
    {
        return;
    }

    SwordCollider = Sword->GetChildActor()->FindComponentByClass<UBoxComponent>();
    if (!SwordCollider)
    {
        return;
    }


    SwordCollider->OnComponentBeginOverlap.AddDynamic(this, &ASW_Brall::OnSwordOverlap);
    SwordCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    SwordCollider->SetHiddenInGame(false);
    SwordCollider->SetVisibility(true);
}

// 평타 콤보용 ==============================================================================
void ASW_Brall::OnSwordOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor != this && !AlreadyHitActors.Contains(OtherActor))
    {
        int32 Damage = 15;
        if (CurrentComboIndex == 2) // 1타
        {
            Damage = 20;
        }

        FDamageEvent DamageEvent;
        OtherActor->TakeDamage(Damage, DamageEvent, GetController(), this);
        AlreadyHitActors.Add(OtherActor);
    }
}

void ASW_Brall::SwordAttackStart()
{
    AlreadyHitActors.Empty();

    if (SwordCollider)  // null 체크 추가
    {
        SwordCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    }
}

void ASW_Brall::SwordAttackEnd()
{
    if (SwordCollider)  // null 체크 추가
    {
        SwordCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    }
}
// ===========================================================================================



// 대쉬 스킬용 ================================================================================
void ASW_Brall::DashSkill()
{
    Super::DashSkill();

    GetWorldTimerManager().SetTimer(
        DashTimerHandle,
        this,
        &ASW_Brall::ExecuteDesh,
        0.3f,
        false
    );
}

void ASW_Brall::ExecuteDesh()
{
    FVector DashDirection = GetActorForwardVector().GetSafeNormal();
    float DashSpeed = 2000.f;

    AlreadyHitActors.Empty();
    DashCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly); // 박스 ON

    UCharacterMovementComponent* MoveComp = GetCharacterMovement();
    MoveComp->BrakingFrictionFactor = 0.f;
    MoveComp->BrakingDecelerationWalking = 0.f;

    LaunchCharacter(DashDirection * DashSpeed, true, true);

    FTimerHandle DashResetHandle;
    GetWorldTimerManager().SetTimer(DashResetHandle, FTimerDelegate::CreateLambda([this, MoveComp]()
        {
            MoveComp->BrakingFrictionFactor = 2.f;
            MoveComp->BrakingDecelerationWalking = 2048.f;
            DashCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision); // 박스 off
        }), 0.5f, false);
}

void ASW_Brall::OnDashBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor != this && !AlreadyHitActors.Contains(OtherActor))
    {
        int32 Damage = 30;

        FDamageEvent DamageEvent;
        OtherActor->TakeDamage(Damage, DamageEvent, GetController(), this);
        AlreadyHitActors.Add(OtherActor);
    }
}
// ==============================================================================================
