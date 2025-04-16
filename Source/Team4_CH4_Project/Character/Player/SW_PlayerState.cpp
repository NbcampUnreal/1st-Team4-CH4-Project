// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_PlayerState.h"
#include "Net/UnrealNetwork.h"

ASW_PlayerState::ASW_PlayerState()
{
	PlayerKill = 0;
	bIsWon = true;
}

void ASW_PlayerState::SetPlayerKill(int Count)
{
	PlayerKill += Count;
	UE_LOG(LogTemp, Warning, TEXT("Player Kill: %d"), PlayerKill);
}

int ASW_PlayerState::GetPlayerKill() const
{
	return PlayerKill;
}

void ASW_PlayerState::SetbIsWon(bool IsWon)
{
	bIsWon = IsWon;
}

bool ASW_PlayerState::GetbIsWon() const
{
	return bool(bIsWon);
}

void ASW_PlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ASW_PlayerState, PlayerKill);

}
