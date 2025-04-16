#include "SW_SkillEffectActor.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"
#include "TimerManager.h"
#include "Engine/World.h"

ASkillEffectActor::ASkillEffectActor()
{
    PrimaryActorTick.bCanEverTick = false;

    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

    NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
    NiagaraComponent->SetupAttachment(RootComponent);

    AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
    AudioComponent->SetupAttachment(RootComponent);
    AudioComponent->bAutoActivate = false;
}

void ASkillEffectActor::BeginPlay()
{
    Super::BeginPlay();
}

void ASkillEffectActor::InitEffect(FVector Location, FRotator Rotation)
{
    SetActorLocation(Location);
    SetActorRotation(Rotation);

    if (NiagaraComponent)
    {
        NiagaraComponent->Activate(true);
    }

    if (AudioComponent)
    {
        AudioComponent->Play();
    }

    GetWorldTimerManager().SetTimer(DestroyTimerHandle, this, &ASkillEffectActor::DestroySelf, LifeTime, false);
}

void ASkillEffectActor::DestroySelf()
{
    Destroy();
}
