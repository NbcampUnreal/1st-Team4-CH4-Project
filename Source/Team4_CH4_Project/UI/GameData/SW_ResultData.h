// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SW_ResultData.generated.h"

USTRUCT(BlueprintType)
struct FSW_ResultData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString PlayerName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Rank;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bHasWon;
};