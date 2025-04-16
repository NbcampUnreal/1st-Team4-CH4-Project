// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SW_TimeWidget.generated.h"

class UTextBlock;

UCLASS()
class TEAM4_CH4_PROJECT_API USW_TimeWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* TimeText;

	FTimerHandle StopHandle;
	FTimerHandle UpdateHandle;

	UFUNCTION(BlueprintCallable)
	void StartTimer(const int32& Seconds);
	UFUNCTION(BlueprintCallable)
	void UpdateTimer();
	UFUNCTION(BlueprintCallable)
	void StopTimer();
};
