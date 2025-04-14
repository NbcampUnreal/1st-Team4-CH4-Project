// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "SW_HPBar.generated.h"

class UProgressBar;
class UTextBlock;

UCLASS()
class TEAM4_CH4_PROJECT_API USW_HPBar : public UWidgetComponent
{
	GENERATED_BODY()
public:
	void UpdateHealthBar(int32 CurrentHealth, int32 MaxHealth);

protected:

	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthBar;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* HealthCount;
};
