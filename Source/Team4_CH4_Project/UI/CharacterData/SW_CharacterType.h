// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SW_CharacterType.generated.h"

UENUM(BlueprintType)
enum class ECharacterType : uint8
{
	Dubu	UMETA(DisplayName = "Dubu"),
	Brall	UMETA(DisplayName = "Brall"),
	Myth	UMETA(DisplayName = "Myth"),
	Void	UMETA(DisplayName = "Void"),
	MAX		UMETA(DisplayName = "MAX")
};

