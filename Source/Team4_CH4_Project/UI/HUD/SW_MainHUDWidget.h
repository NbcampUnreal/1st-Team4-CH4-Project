// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SW_MainHUDWidget.generated.h"

class USW_MinimapWidget;

UCLASS()
class TEAM4_CH4_PROJECT_API USW_MainHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	USW_MinimapWidget* MinimapWidget;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//UUserWidget* NotificationWidget;

	FTimerHandle UpdateHandle;

	UFUNCTION(BlueprintCallable)
	void StartUpdateTimer();
	UFUNCTION(BlueprintCallable)
	void UpdateMinimap();
};
