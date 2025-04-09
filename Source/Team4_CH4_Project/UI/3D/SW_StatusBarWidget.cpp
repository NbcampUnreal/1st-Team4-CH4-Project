// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_StatusBarWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

void USW_StatusBarWidget::UpdateUsername(const FName& Username)
{
	if (IsValid(UsernameText))
	{
		UsernameText->SetText(FText::FromName(Username));
	}
}

void USW_StatusBarWidget::UpdateHealthBar(const int32& CurrentHealth, const int32& MaxHealth)
{
	if (IsValid(HealthBar) && MaxHealth > 0)
	{
		float HealthPercent = float(CurrentHealth) / float(MaxHealth);
		HealthBar->SetPercent(HealthPercent);
	}
}

void USW_StatusBarWidget::UpdateStaminaBar(const int32& CurrentStamina, const int32& MaxStamina)
{
	if (IsValid(HealthBar) && MaxStamina > 0)
	{
		float StaminaPercent = float(CurrentStamina) / float(MaxStamina);
		StaminaBar->SetPercent(StaminaPercent);
	}
}
