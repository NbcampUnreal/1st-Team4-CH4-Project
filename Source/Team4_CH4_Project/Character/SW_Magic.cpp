#include "SW_Magic.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

ASW_Magic::ASW_Magic()
{
    MoveSpeed = 1500.f;
}

void ASW_Magic::BeginPlay()
{
    Super::BeginPlay();
}

void ASW_Magic::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ASW_Magic::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    if (!HasAuthority()) return;

    if (!OtherActor || OtherActor == this || OtherActor == GetInstigator() || OtherActor == GetOwner())
        return;

    if (AlreadyHitActors.Contains(OtherActor)) return;
    AlreadyHitActors.Add(OtherActor);

    UGameplayStatics::ApplyDamage(OtherActor, Damage, GetInstigatorController(), this, UDamageType::StaticClass());

    Destroy();
}

void ASW_Magic::SpawnNiagaraEffect(UNiagaraSystem* NiagaraSystem)
{
    UNiagaraFunctionLibrary::SpawnSystemAttached(
        NiagaraSystem,
        GetRootComponent(),
        NAME_None,
        FVector::ZeroVector,
        FRotator::ZeroRotator,
        EAttachLocation::KeepRelativeOffset,
        true
    );
}
