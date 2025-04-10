// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_StatusBarViewModel.h"

void USW_StatusBarViewModel::SetMaxHealth(const int32& NewMaxHealth)
{
	if (NewMaxHealth <= 0)
	{
		return;
	}
	if (UE_MVVM_SET_PROPERTY_VALUE(MaxHealth, NewMaxHealth))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetHealthPercent);
	}
}

void USW_StatusBarViewModel::SetCurrentHealth(const int32& NewCurrentHealth)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(CurrentHealth, NewCurrentHealth < 0 ? 0 : NewCurrentHealth))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetHealthPercent);
	}
}

float USW_StatusBarViewModel::GetHealthPercent() const
{
	float HealthPercent = 0.f;
	if (MaxHealth > 0)
	{
		HealthPercent = float(CurrentHealth) / float(MaxHealth);
	}
	return HealthPercent;
}

void USW_StatusBarViewModel::SetMaxStamina(const int32& NewMaxStamina)
{
	if (NewMaxStamina <= 0)
	{
		return;
	}
	if (UE_MVVM_SET_PROPERTY_VALUE(MaxStamina, NewMaxStamina))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetStaminaPercent);
	}
	
}

void USW_StatusBarViewModel::SetCurrentStamina(const int32& NewCurrentStamina)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(CurrentStamina, NewCurrentStamina < 0 ? 0 : NewCurrentStamina))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetHealthPercent);
	}
}

float USW_StatusBarViewModel::GetStaminaPercent() const
{
	float StaminaPercent = 0.f;
	if (MaxStamina > 0)
	{
		StaminaPercent = float(CurrentStamina) / float(MaxStamina);
	}
	return StaminaPercent;
}

void USW_StatusBarViewModel::SetUsername(const FName& NewUsername)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(Username, NewUsername))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetUsernameText);
	}
}

FText USW_StatusBarViewModel::GetUsernameText() const
{
	return FText::FromName(Username);
}
