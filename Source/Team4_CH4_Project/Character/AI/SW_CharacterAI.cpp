// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_CharacterAI.h"
#include "AbilitySystem/SW_AbilitySystemComponent.h"
#include "AbilitySystem/SW_AttributeSet.h"

ASW_CharacterAI::ASW_CharacterAI()
{
	AbilitySystemComponent = CreateDefaultSubobject<USW_AbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<USW_AttributeSet>("AttributeSet");
}

void ASW_CharacterAI::BeginPlay()
{
	Super::BeginPlay();

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

