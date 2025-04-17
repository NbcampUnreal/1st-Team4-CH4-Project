// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SW_CharacterType.h"
#include "SW_CharacterDataRow.generated.h"

USTRUCT(BlueprintType)
struct FCharacterDataRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECharacterType CharacterType = ECharacterType::MAX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText IntroText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* CharacterImage = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UTexture2D> CharacterFullImage = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Defense = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxHealth = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxStamina = 0;
};