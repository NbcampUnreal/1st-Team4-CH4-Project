#include "SW_VoidSpawnActor.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "NiagaraFunctionLibrary.h"
#include "Engine/DamageEvents.h"

ASW_VoidSpawnActor::ASW_VoidSpawnActor()
{
    bReplicates = true;
    SetReplicateMovement(false);

    PrimaryActorTick.bCanEverTick = false;

    VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualMesh"));
    RootComponent = VisualMesh;
    VisualMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    VisualMesh->SetRelativeScale3D(FVector(2.f));
}

void ASW_VoidSpawnActor::BeginPlay()
{
    Super::BeginPlay();

    // 2초 후 폭발
    FTimerHandle ExplosionHandle;
    GetWorldTimerManager().SetTimer(ExplosionHandle, [this]()
        {
            ApplyDamage();
            Destroy();
        }, 2.0f, false);
}

void ASW_VoidSpawnActor::ApplyDamage()
{
    if (!OwnerCharacter) return;

    // FX는 모두에게 보이게 멀티캐스트 호출
    Multicast_PlayExplosionFX();

    FVector Origin = GetActorLocation() + GetActorRotation().RotateVector(Offset);
    float Radius = Range.X;

    if (ExplosionNiagaraSystem)
    {
        UNiagaraFunctionLibrary::SpawnSystemAtLocation(
            GetWorld(),
            ExplosionNiagaraSystem,
            Origin,
            GetActorRotation(),
            FVector(1.f),
            true,  // bAutoDestroy
            true   // bAutoActivate
        );
    }

    // 데미지 처리
    TArray<AActor*> HitActors;
    TArray<AActor*> Ignore;
    Ignore.Add(this);
    Ignore.Add(OwnerCharacter);

    UKismetSystemLibrary::SphereOverlapActors(
        GetWorld(),
        Origin,
        Radius,
        TArray<TEnumAsByte<EObjectTypeQuery>>{UEngineTypes::ConvertToObjectType(ECC_Pawn)},
        ACharacter::StaticClass(),
        Ignore,
        HitActors
    );

    for (AActor* Target : HitActors)
    {
        if (!Target || AlreadyHitActors.Contains(Target)) continue;

        FDamageEvent Event;
        Target->TakeDamage(Damage * DamageMultiplier, Event, OwnerCharacter->GetInstigatorController(), this);
        AlreadyHitActors.Add(Target);
    }

    DrawDebugSphere(GetWorld(), Origin, Radius, 32, FColor::Purple, false, 2.f);
}

void ASW_VoidSpawnActor::Multicast_PlayExplosionFX_Implementation()
{
    if (ExplosionNiagaraSystem)
    {
        UNiagaraFunctionLibrary::SpawnSystemAtLocation(
            GetWorld(),
            ExplosionNiagaraSystem,
            GetActorLocation() + GetActorRotation().RotateVector(Offset),
            GetActorRotation(),
            FVector(1.f),
            true,
            true
        );
    }
}