// Fill out your copyright notice in the Description page of Project Settings.


#include "Team4_CH4_Project/Game/GameState/SW_GameState.h"
#include "Team4_CH4_Project/Game/GameMode/SW_GameMode.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/PlayerController.h"
#include "EngineUtils.h"
#include "GameFramework/GameSession.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerState.h"
#include "Player/SW_PlayerState.h"

ASW_GameState::ASW_GameState()
{
	PrimaryActorTick.bCanEverTick = true;
	RoundDuration = 5.f;
	RoundTimeLeft = RoundDuration;
	CurrentPlayerAmount = 0;
	bPlayerIn = false;
	bGameEnd = false;
	if (ASW_GameMode* SWGameMode = (ASW_GameMode*)(GetWorld()->GetAuthGameMode()))
	{
		PlayerControllers = SWGameMode->GetPlayerControllers();
	}
}

void ASW_GameState::BeginPlay()
{
	Super::BeginPlay();

}
void ASW_GameState::ShowDebug() const
{
	UE_LOG(LogTemp, Warning, TEXT("CurrentPlayer is : %d"),CurrentPlayerAmount);
}

void ASW_GameState::OnRep_DoEndGame() 
{
	if (ASW_GameMode* SWGamemode = (ASW_GameMode*)GetWorld()->GetAuthGameMode())
	{
		SWGamemode->Multicast_EndGame_Implementation();
	}
	bGameEnd = true;
}

void ASW_GameState::OnRep_RoundOver()
{
	for (APlayerController* PlayerController : PlayerControllers)
	{
		PlayerStatesByKills.Add(PlayerController->GetPlayerState<ASW_PlayerState*>);
	}
}

void ASW_GameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (HasAuthority())
	{
		if (RoundTimeLeft > -0.1f)
		{
			RoundTimeLeft -= DeltaSeconds;
			UE_LOG(LogTemp, Warning, TEXT("TimeLeft : %f"),RoundTimeLeft);
		}
		if (RoundTimeLeft < 0 && !bGameEnd)
		{
			OnRep_DoEndGame();
		}
	}
}

void ASW_GameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASW_GameState, RoundDuration);
	DOREPLIFETIME(ASW_GameState, RoundTimeLeft);
	DOREPLIFETIME(ASW_GameState, CurrentPlayerAmount);
	DOREPLIFETIME(ASW_GameState, bPlayerIn);
}

void ASW_GameState::SetCurrentPlayerAmount(int AddAmount)
{
	CurrentPlayerAmount += AddAmount;

	if (CurrentPlayerAmount >= 2) bPlayerIn = true;
	if (bPlayerIn && CurrentPlayerAmount <= 1)
	{
		OnRep_DoEndGame();
	}
}

float ASW_GameState::GetRoundTimeLeft()
{
	return RoundTimeLeft;
}