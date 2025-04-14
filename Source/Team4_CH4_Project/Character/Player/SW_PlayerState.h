// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "SW_PlayerState.generated.h"

class USW_AbilitySystemComponent;
class USW_AttributeSet;

UCLASS()
class TEAM4_CH4_PROJECT_API ASW_PlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	ASW_PlayerState();

	void SetPlayerKill(int Count);

	int GetPlayerKill() const;
protected:
	UPROPERTY()
	TObjectPtr<USW_AbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<USW_AttributeSet> AttributeSet;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UPROPERTY(Replicated)
	int PlayerKill;
public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	USW_AttributeSet* GetAttributeSet() const;
};
