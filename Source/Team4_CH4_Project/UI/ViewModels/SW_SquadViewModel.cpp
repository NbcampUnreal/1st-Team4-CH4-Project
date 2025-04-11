// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_SquadViewModel.h"

void USW_SquadViewModel::SetMaxHealth(const int32& NewMaxHealth)
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

void USW_SquadViewModel::SetCurrentHealth(const int32& NewCurrentHealth)
{
	if (NewCurrentHealth <= 0)
	{
		return;
	}
	if (UE_MVVM_SET_PROPERTY_VALUE(CurrentHealth, NewCurrentHealth))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetHealthPercent);
	}
}

float USW_SquadViewModel::GetHealthPercent() const
{
	float HealthPercent = 0.f;
	if (MaxHealth > 0)
	{
		HealthPercent = float(CurrentHealth) / float(MaxHealth);
	}
	return HealthPercent;
}

void USW_SquadViewModel::SetUsername(const FName& NewUsername)
{
	Username = NewUsername;
}
