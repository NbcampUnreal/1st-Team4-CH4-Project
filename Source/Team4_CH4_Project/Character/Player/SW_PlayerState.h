// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SW_PlayerState.generated.h"

UCLASS()
class TEAM4_CH4_PROJECT_API ASW_PlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	ASW_PlayerState();

	void SetPlayerKill(int Count);

	int GetPlayerKill() const;
protected:

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UPROPERTY(Replicated)
	int PlayerKill;
public:
};
