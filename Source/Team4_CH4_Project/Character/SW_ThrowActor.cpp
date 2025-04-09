#include "SW_ThrowActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/DamageType.h"
#include "Engine/DamageEvents.h" // FDamageEvent 정의를 위해 추가
#include "Kismet/GameplayStatics.h"

ASW_ThrowActor::ASW_ThrowActor()
{
    bReplicates = true;
    SetReplicateMovement(true);

    PrimaryActorTick.bCanEverTick = true;

    // Static Mesh 컴포넌트 설정 (블루프린트에서 메시 지정)
    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
    RootComponent = MeshComp;
    MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision); // 메시 자체는 충돌 X

    // 충돌용 박스 컴포넌트 설정
    CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
    CollisionComp->SetupAttachment(RootComponent);
    CollisionComp->SetBoxExtent(FVector(50.f, 50.f, 50.f)); // 충돌 크기 설정
    CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComp->SetCollisionResponseToAllChannels(ECR_Ignore);
    CollisionComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap); // 적 캐릭터와 충돌
    CollisionComp->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap); // 벽과 충돌
    CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ASW_ThrowActor::OnOverlapBegin);
}

void ASW_ThrowActor::BeginPlay()
{
    Super::BeginPlay();
    SetLifeSpan(2.f); // 2초 후 자동 파괴
}

void ASW_ThrowActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // 앞으로 이동
    FVector NewLocation = GetActorLocation() + (GetActorForwardVector() * MoveSpeed * DeltaTime);
    SetActorLocation(NewLocation);
}

void ASW_ThrowActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    if (!HasAuthority()) return;
    ApplyThrowDamage(OtherActor);
}

void ASW_ThrowActor::ApplyThrowDamage(AActor* OtherActor)
{
    if (!OtherActor || OtherActor == this || OtherActor == GetInstigator() || OtherActor == GetOwner())
        return;

    if (AlreadyHitActors.Contains(OtherActor)) return;
    AlreadyHitActors.Add(OtherActor);

    FDamageEvent DamageEvent;
    OtherActor->TakeDamage(Damage, DamageEvent, GetInstigatorController(), this);

    Destroy();
}