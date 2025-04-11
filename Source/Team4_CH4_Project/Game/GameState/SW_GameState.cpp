// Fill out your copyright notice in the Description page of Project Settings.


#include "Team4_CH4_Project/Game/GameState/SW_GameState.h"

ASW_GameState::ASW_GameState()
{
}

void ASW_GameState::BeginPlay()
{
	Super::BeginPlay();
}

void ASW_GameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	int Controllers = GetWorld()->GetNumPlayerControllers();
	UE_LOG(LogTemp, Warning, TEXT("The PlayerController value is: %d"), Controllers);
}
