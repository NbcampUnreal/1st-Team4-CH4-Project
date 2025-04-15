// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_PlayerState.h"
#include "Net/UnrealNetwork.h"

ASW_PlayerState::ASW_PlayerState()
{
	
}

void ASW_PlayerState::SetPlayerKill(int Count)
{
	PlayerKill += Count;
}

int ASW_PlayerState::GetPlayerKill() const
{
	return PlayerKill;
}

void ASW_PlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ASW_PlayerState, PlayerKill);

}