// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_TimeWidget.h"
#include "MVVMViewModelBase.h"

void USW_TimeWidget::SetViewModel(UMVVMViewModelBase* InViewModel)
{
	if (IsValid(InViewModel))
	{
		ViewModel = InViewModel;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TimeWidget::SetViewModel : InViewModel is invalid"))
	}
}
