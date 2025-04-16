// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_TimeViewModel.h"

void USW_TimeViewModel::SetRemainingTimeSeconds(const int32& NewTimeSeconds)
{
	if (NewTimeSeconds > 0)
	{
		UE_MVVM_SET_PROPERTY_VALUE(RemainingTimeSeconds, NewTimeSeconds);
		//UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetRemainingTimeText);
	}
}

/*
FText USW_TimeViewModel::GetRemainingTimeText() const
{
	FString ReturnString = "00:00";
	if (RemainingTimeSeconds > 0)
	{
		int32 Minutes = RemainingTimeSeconds / 60;
		int32 Seconds = RemainingTimeSeconds - Minutes * 60;
		ReturnString = FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds);
	}
	return FText::FromString(ReturnString);
}
*/
