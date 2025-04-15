// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_ResultsViewModel.h"

void USW_ResultsViewModel::SetPlayTimeSeconds(const int32& Seconds)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(PlayTimeSeconds, Seconds))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetPlayTimeText);
	}
}

FText USW_ResultsViewModel::GetPlayTimeText() const
{
	FString ReturnString = "00:00";
	if (PlayTimeSeconds > 0)
	{
		int32 Minutes = PlayTimeSeconds / 60;
		int32 Seconds = PlayTimeSeconds - Minutes * 60;
		ReturnString = FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds);
	}
	return FText::FromString(ReturnString);
}

void USW_ResultsViewModel::SetHasWon(const bool& bHasWon)
{
	UE_MVVM_SET_PROPERTY_VALUE(HasWon, bHasWon);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetHasWon);
}

void USW_ResultsViewModel::SetResultToAdd(const FSW_ResultData& InData)
{
	if (ResultToAdd.PlayerName != InData.PlayerName)
	{
		ResultToAdd.PlayerName = InData.PlayerName;
		ResultToAdd.Rank = InData.Rank;
		ResultToAdd.bHasWon = InData.bHasWon;

		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetResultToAdd);
	}
}
