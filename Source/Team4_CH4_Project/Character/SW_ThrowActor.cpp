#include "SW_ThrowActor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "Engine/EngineTypes.h"
#include "Engine/DamageEvents.h"

ASW_ThrowActor::ASW_ThrowActor()
{
    PrimaryActorTick.bCanEverTick = false;

    // 충돌용 Box 컴포넌트
    Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
    Collision->SetBoxExtent(FVector(10.f, 10.f, 10.f)); // 박스 크기 설정 (구형 반지름 10.f에 맞게 조정)
    Collision->SetCollisionProfileName(TEXT("Projectile"));
    Collision->SetNotifyRigidBodyCollision(true);
    Collision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    Collision->SetCollisionObjectType(ECC_WorldDynamic);
    Collision->SetCollisionResponseToAllChannels(ECR_Ignore);
    Collision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
    Collision->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
    RootComponent = Collision;

    // 충돌 이벤트 바인딩
    Collision->OnComponentHit.AddDynamic(this, &ASW_ThrowActor::OnHit);

    // 투사체 이동 컴포넌트
    Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
    Movement->InitialSpeed = 1500.f;
    Movement->MaxSpeed = 1500.f;
    Movement->ProjectileGravityScale = 0.f;

    // StaticMesh 컴포넌트 추가
    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    StaticMesh->SetupAttachment(RootComponent);
    StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision); // 충돌 비활성화
    StaticMesh->SetCollisionResponseToAllChannels(ECR_Ignore); // 모든 채널에 대해 충돌 무시

    // 5초 후 자동 파괴
    InitialLifeSpan = 2.f;

    // 기본 데미지 설정
    Damage = 20.f;
}

void ASW_ThrowActor::BeginPlay()
{
    Super::BeginPlay();

    if (IgnoredActor)
    {
        Collision->IgnoreActorWhenMoving(IgnoredActor, true);
    }
}

void ASW_ThrowActor::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (OtherActor && OtherActor != this && OtherActor != IgnoredActor)
    {
        FPointDamageEvent PointDamageEvent;
        PointDamageEvent.Damage = Damage;
        PointDamageEvent.HitInfo = Hit;
        PointDamageEvent.ShotDirection = GetActorForwardVector();
        OtherActor->TakeDamage(Damage, PointDamageEvent, GetInstigatorController(), this);
    }
    Destroy();
}