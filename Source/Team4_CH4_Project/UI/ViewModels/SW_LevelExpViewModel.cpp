// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_LevelExpViewModel.h"

void USW_LevelExpViewModel::SetMaxExp(const int32& NewMaxExp)
{
	if (NewMaxExp <= 0)
	{
		return;
	}
	if (UE_MVVM_SET_PROPERTY_VALUE(MaxExp, NewMaxExp))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetExpPercent);
	}
}

void USW_LevelExpViewModel::SetCurrentExp(const int32& NewCurrentExp)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(CurrentExp, NewCurrentExp < 0 ? 0 : NewCurrentExp))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetExpPercent);
	}
}

float USW_LevelExpViewModel::GetExpPercent() const
{
	float ExpPercent = 0.f;
	if (MaxExp > 0)
	{
		ExpPercent = float(CurrentExp) / float(MaxExp);
	}
	return ExpPercent;
}

void USW_LevelExpViewModel::SetCurrentLevel(const int32& NewCurrentLevel)
{
	if (NewCurrentLevel <= 0)
	{
		return;
	}
	if (UE_MVVM_SET_PROPERTY_VALUE(CurrentLevel, NewCurrentLevel))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetCurrentLevelText);
	}
}

FText USW_LevelExpViewModel::GetCurrentLevelText() const
{
	return FText::FromString(FString::FromInt(CurrentLevel));
}
