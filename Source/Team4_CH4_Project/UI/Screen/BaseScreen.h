// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseScreen.generated.h"

class UScreenManager;

UCLASS()
class TEAM4_CH4_PROJECT_API UBaseScreen : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category = "Animations", meta=(BindWidgetAnimOptional))
	UWidgetAnimation* EnterScreenAnim;
	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (BindWidgetAnimOptional))
	UWidgetAnimation* ExitScreenAnim;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Manager")
	UScreenManager* ScreenManager;

	UFUNCTION(BlueprintPure, Category = "Manager")
	UScreenManager* GetScreenManager() { return ScreenManager; }
	UFUNCTION(BlueprintCallable, Category = "Manager")
	void SetScreenManager(UScreenManager* InScreenManager) { ScreenManager = InScreenManager; }
};
