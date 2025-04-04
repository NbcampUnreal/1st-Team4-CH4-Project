// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SW_PlayerAnimLayerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USW_PlayerAnimLayerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TEAM4_CH4_PROJECT_API ISW_PlayerAnimLayerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void LocomotionLayer(FVector MovementInput);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void AttackLayer();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SkillLayer();
};
