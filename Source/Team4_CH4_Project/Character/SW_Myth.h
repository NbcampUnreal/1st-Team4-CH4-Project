// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SW_CharacterBase.h"
#include "SW_Myth.generated.h"

/**
 * 
 */
UCLASS()
class TEAM4_CH4_PROJECT_API ASW_Myth : public ASW_CharacterBase
{
	GENERATED_BODY()
public:
	ASW_Myth();

public:
	virtual void BeginPlay() override;
	
};

