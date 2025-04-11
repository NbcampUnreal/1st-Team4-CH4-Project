// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_PlayerState.h"
#include "Team4_CH4_Project/AbilitySystem/SW_AbilitySystemComponent.h"
#include "Team4_CH4_Project/AbilitySystem/SW_AttributeSet.h"

ASW_PlayerState::ASW_PlayerState()
{
	SetNetUpdateFrequency(100.f);

	AbilitySystemComponent = CreateDefaultSubobject<USW_AbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<USW_AttributeSet>("AttributeSet");
}

UAbilitySystemComponent* ASW_PlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

USW_AttributeSet* ASW_PlayerState::GetAttributeSet() const
{
	return AttributeSet;
}
