#include "SW_MythSpawnActor.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"
#include "Engine/DamageEvents.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"
#include "UObject/ConstructorHelpers.h"

ASW_MythSpawnActor::ASW_MythSpawnActor()
{
    bReplicates = true;
    SetReplicateMovement(false);

    PrimaryActorTick.bCanEverTick = true; // Tick 활성화

    // 시각용 메시 (Root로 사용)
    VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Visual"));
    RootComponent = VisualMesh;
    VisualMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    VisualMesh->SetRelativeScale3D(FVector(2.0f));

    // 기본 메시 설정 (큐브)
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube"));
    if (CubeMesh.Succeeded())
    {
        VisualMesh->SetStaticMesh(CubeMesh.Object);
        VisualMesh->SetMaterial(0, nullptr);
    }
}

void ASW_MythSpawnActor::BeginPlay()
{
    Super::BeginPlay();
    SetLifeSpan(2.f);
}

void ASW_MythSpawnActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!bHasAppliedDamage)
    {
        ApplyDamage();
        bHasAppliedDamage = true; // 한 번만 데미지 적용
    }
}

void ASW_MythSpawnActor::ApplyDamage()
{
    if (!OwnerCharacter) return;

    // 충돌 중심 위치 계산
    FVector Origin = GetActorLocation() + GetActorRotation().RotateVector(Offset);
    float Radius = Range.X;

    TArray<AActor*> Overlapped;
    TArray<AActor*> Ignore;
    Ignore.Add(this);
    Ignore.Add(OwnerCharacter);

    // 범위 내 캐릭터들 탐지
    UKismetSystemLibrary::SphereOverlapActors(
        GetWorld(),
        Origin,
        Radius,
        TArray<TEnumAsByte<EObjectTypeQuery>>{ UEngineTypes::ConvertToObjectType(ECC_Pawn) },
        ACharacter::StaticClass(),
        Ignore,
        Overlapped
    );

    // 겹쳐 있는 적들에게 데미지 적용
    for (AActor* Target : Overlapped)
    {
        if (!Target || AlreadyHitActors.Contains(Target)) continue;

        if (ACharacter* HitChar = Cast<ACharacter>(Target))
        {
            AController* InstigatorController = OwnerCharacter->GetInstigatorController();
            if (!InstigatorController && OwnerCharacter->GetOwner())
            {
                InstigatorController = Cast<AController>(OwnerCharacter->GetOwner());
            }

            if (InstigatorController)
            {
                FDamageEvent Event;
                float FinalDamage = Damage * DamageMultiplier;
                HitChar->TakeDamage(FinalDamage, Event, InstigatorController, OwnerCharacter);
                AlreadyHitActors.Add(HitChar);
            }
        }
    }

    // 디버그용 시각화
    DrawDebugSphere(GetWorld(), Origin, Radius, 16, FColor::Red, false, 2.f);
}