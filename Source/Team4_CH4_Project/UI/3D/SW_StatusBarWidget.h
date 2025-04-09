// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SW_StatusBarWidget.generated.h"

class UTextBlock;
class UProgressBar;

UCLASS()
class TEAM4_CH4_PROJECT_API USW_StatusBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* UsernameText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* HealthBar;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* StaminaBar;

	UFUNCTION(BlueprintCallable)
	void UpdateUsername(const FName& Username);
	UFUNCTION(BlueprintCallable)
	void UpdateHealthBar(const int32& CurrentHealth, const int32& MaxHealth);
	UFUNCTION(BlueprintCallable)
	void UpdateStaminaBar(const int32& CurrentStamina, const int32& MaxStamina);
};
