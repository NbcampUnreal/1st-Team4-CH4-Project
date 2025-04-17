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
	UUserWidget* PlayerInfoWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UUserWidget* SkillSlotWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UUserWidget* TimeWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	USW_MinimapWidget* MinimapWidget;
	UPROPERTY(Transient, meta=(BindWidgetAnim))
	UWidgetAnimation* EnterAnim;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//UUserWidget* NotificationWidget;

	FWidgetAnimationDynamicEvent EnterAnimFinished;
	FTimerHandle UpdateHandle;

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void DisplayWidgets();
	UFUNCTION(BlueprintCallable)
	void StartUpdateTimer();
	UFUNCTION(BlueprintCallable)
	void UpdateMinimap();
};
