#include "SW_Arrow.h"
#include "SW_MythSpawnActor.h"
#include "SW_CharacterBase.h"
#include "Engine/Engine.h"

ASW_Arrow::ASW_Arrow()
{
	MoveSpeed = 2500.f;
	LifeSpan = 3.f;
	Damage = 20.f;
}

void ASW_Arrow::BeginPlay()
{
	Super::BeginPlay();
}

void ASW_Arrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
