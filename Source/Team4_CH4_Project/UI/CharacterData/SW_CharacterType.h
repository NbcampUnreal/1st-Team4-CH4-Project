// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SW_CharacterType.generated.h"

UENUM(BlueprintType)
enum class ECharacterType : uint8
{
	START,
	Dubu	UMETA(DisplayName = "Dubu"),
	Brall	UMETA(DisplayName = "Brall"),
	Myth	UMETA(DisplayName = "Myth"),
	Void	UMETA(DisplayName = "Void"),
	MAX		UMETA(DisplayName = "MAX")
};

UENUM(BlueprintType)
enum class ESkillType : uint8
{
	Attack	UMETA(DisplayName = "Attack"),
	Guard	UMETA(DisplayName = "Guard"),
	Dash	UMETA(DisplayName = "Dash"),
	Skill1	UMETA(DisplayName = "Skill1"),
	Skill2	UMETA(DisplayName = "Skill2"),
	Skill3	UMETA(DisplayName = "Skill3"),
	MAX		UMETA(DisplayName = "MAX")
};
