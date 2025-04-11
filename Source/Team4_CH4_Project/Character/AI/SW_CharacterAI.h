// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Team4_CH4_Project/Character/SW_CharacterBase.h"
#include "SW_CharacterAI.generated.h"


UCLASS()
class TEAM4_CH4_PROJECT_API ASW_CharacterAI : public ASW_CharacterBase
{
	GENERATED_BODY()
public:
	ASW_CharacterAI();

protected:
	virtual void BeginPlay() override;


};
