// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_TimeWidget.h"
//#include "Components/TextBlock.h"

//void USW_TimeWidget::StartTimer(const int32& Seconds)
//{
//	if (GetWorld() && !GetWorld()->bIsTearingDown)
//	{
//		GetWorld()->GetTimerManager().SetTimer(
//			StopHandle,
//			this,
//			&USW_TimeWidget::StopTimer,
//			float(Seconds),
//			false
//		);
//
//		GetWorld()->GetTimerManager().SetTimer(
//			UpdateHandle,
//			this,
//			&USW_TimeWidget::UpdateTimer,
//			0.1f,
//			true
//		);
//	}
//}
//
//void USW_TimeWidget::UpdateTimer()
//{
//	if (TimeText && GetWorld())
//	{
//		float RemainingTime = GetWorld()->GetTimerManager().GetTimerRemaining(StopHandle);
//		int32 Minutes = RemainingTime / 60;
//		int32 Seconds = RemainingTime - Minutes * 60;
//		FText RemainingTimeText = FText::FromString(FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds));
//		TimeText->SetText(RemainingTimeText);
//	}
//}
//
//void USW_TimeWidget::StopTimer()
//{
//	if (GetWorld() && !GetWorld()->bIsTearingDown)
//	{
//		GetWorld()->GetTimerManager().ClearTimer(UpdateHandle);
//	}
//}
