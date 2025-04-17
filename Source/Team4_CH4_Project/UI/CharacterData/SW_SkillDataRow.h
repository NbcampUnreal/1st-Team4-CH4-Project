// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SW_CharacterType.h"
#include "SW_SkillDataRow.generated.h"

USTRUCT(BlueprintType)
struct FSkillDataRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECharacterType CharacterType = ECharacterType::MAX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* AttackIcon = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* GuardIcon = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* DashIcon = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Skill1Icon = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Skill2Icon = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Skill3Icon = nullptr;
};
