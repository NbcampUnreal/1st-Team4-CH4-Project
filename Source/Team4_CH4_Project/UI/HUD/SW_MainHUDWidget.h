// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SW_MainHUDWidget.generated.h"

UCLASS()
class TEAM4_CH4_PROJECT_API USW_MainHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UUserWidget* PlayerInfoWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UUserWidget* SkillSlotWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UUserWidget* TimeWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UUserWidget* MinimapWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UUserWidget* QuickSlotWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetOptional))
	UUserWidget* SquadInfoWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UUserWidget* NotificationWidget;
};
