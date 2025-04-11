// Fill out your copyright notice in the Description page of Project Settings.


#include "Team4_CH4_Project/Game/GameState/SW_GameState.h"
#include "Team4_CH4_Project/Game/GameMode//SW_GameMode.h"
#include "Net/UnrealNetwork.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerState.h"
ASW_GameState::ASW_GameState()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	RoundDuration = 240.0f;
	RoundTime = RoundDuration;
	bIsRoundOver = false;
	RemainingPlayers = 0;
	WinningPlayerName = FString("");
}

void ASW_GameState::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		GetWorldTimerManager().SetTimer(RoundTimerHandle, this, &ASW_GameState::UpdateRoundTime, 1.0f, true);
		GetWorldTimerManager().SetTimer(CheckStateTimerHandle, this, &ASW_GameState::CheckGameState, 1.0f, true);
	}
}

void ASW_GameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ASW_GameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASW_GameState, RoundTime);
	DOREPLIFETIME(ASW_GameState, bIsRoundOver);
	DOREPLIFETIME(ASW_GameState, RemainingPlayers);
	DOREPLIFETIME(ASW_GameState, WinningPlayerName);
}

void ASW_GameState::SetRoundTime(float SetCurrentRoundTime)
{
	RoundTime = SetCurrentRoundTime;
}

void ASW_GameState::UpdateRoundTime()
{
	if (HasAuthority())
	{
		RoundTime -= 1.0f;
		if (RoundTime <= 0.0f && !bIsRoundOver)
		{
			bIsRoundOver = true;
			GetWorldTimerManager().ClearTimer(RoundTimerHandle);
			// 게임 종료 로직 (결과창 표시 등)은 GameMode에서 처리
		}
	}
}

void ASW_GameState::CheckGameState()
{
	if (HasAuthority() && !bIsRoundOver)
	{
		int32 AlivePlayers = 0;
		//ASWCharacterBase* LastAlivePlayer = nullptr;

		/*for (TActorIterator<ASWCharacterBase> It(GetWorld()); It; ++It)
		{
			ASWCharacterBase* CurrentCharacter = *It;
			if (!CurrentCharacter->IsPlayerDead())
			{
				AlivePlayers++;
				LastAlivePlayer = CurrentCharacter;
			}
		}*/

		RemainingPlayers = AlivePlayers;

		if (AlivePlayers <= 1)
		{
			bIsRoundOver = true;
			GetWorldTimerManager().ClearTimer(CheckStateTimerHandle);
			/*
			if (AlivePlayers == 1 && LastAlivePlayer)
			{
				APlayerState* PlayerState = LastAlivePlayer->GetPlayerState();
				if (PlayerState)
				{
					WinningPlayerName = PlayerState->GetPlayerName();
				}
			}*/

			// 게임 종료 로직 (결과창 표시 등)은 GameMode에서 처리
			if (ASW_GameMode* GameMode = Cast<ASW_GameMode>(GetWorld()->GetAuthGameMode()))
			{
				GameMode->HandleGameOver();
			}
		}
	}
}

void ASW_GameState::EndGame() const
{
	GetWorldTimerManager().ClearAllTimersForObject(this);
	UE_LOG(LogTemp, Warning, TEXT("Game Is Over!"));
}
