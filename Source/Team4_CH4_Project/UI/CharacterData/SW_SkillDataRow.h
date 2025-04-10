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
	ECharacterType CharacterType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* AttackIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* GuardIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* DashIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Skill1Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Skill2Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Skill3Icon;
};
