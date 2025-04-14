// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_PlayerState.h"
#include "Team4_CH4_Project/AbilitySystem/SW_AbilitySystemComponent.h"
#include "Team4_CH4_Project/AbilitySystem/SW_AttributeSet.h"
#include "Net/UnrealNetwork.h"

ASW_PlayerState::ASW_PlayerState()
{
	SetNetUpdateFrequency(100.f);

	AbilitySystemComponent = CreateDefaultSubobject<USW_AbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<USW_AttributeSet>("AttributeSet");
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

UAbilitySystemComponent* ASW_PlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

USW_AttributeSet* ASW_PlayerState::GetAttributeSet() const
{
	return AttributeSet;
}
