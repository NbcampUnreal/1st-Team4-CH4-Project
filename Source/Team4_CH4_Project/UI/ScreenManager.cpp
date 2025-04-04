// Fill out your copyright notice in the Description page of Project Settings.

#include "ScreenManager.h"
#include "Screen/BaseScreen.h"
#include "Blueprint/UserWidget.h"


void UScreenManager::EnterScreen(EScreenType ScreenType)
{
	if (UUserWidget** ActiveScreenPtr = ActiveScreensMap.Find(ScreenType))
	{
		UE_LOG(LogTemp, Warning, TEXT("UScreenManager::EnterScreen : screen is already active"));
		(*ActiveScreenPtr)->AddToViewport();
		return;
	}

	if (!ScreenClassMap.Contains(ScreenType))
	{
		UE_LOG(LogTemp, Warning, TEXT("UScreenManager::EnterScreen : key not valid, cannot find the class"));
		return;
	}

	TSubclassOf<UUserWidget> ScreenClass = ScreenClassMap[ScreenType];
	if (ScreenClass)
	{
		if (UUserWidget* NewWidget = CreateWidget<UUserWidget>(GetGameInstance(), ScreenClass))
		{
			if (UBaseScreen* NewScreen = Cast<UBaseScreen>(NewWidget))
			{
				NewScreen->SetScreenManager(this);
			}

			NewWidget->AddToViewport();
			ActiveScreensMap.Add(ScreenType, NewWidget);
		}
	}
}

void UScreenManager::ExitScreen(EScreenType InScreenToRemove, EScreenType InScreenToEnter)
{
	if (UUserWidget** ActiveWidgetPtr = ActiveScreensMap.Find(InScreenToRemove))
	{
		ScreenToRemove = InScreenToRemove;
		ScreenToEnter = InScreenToEnter;

		UUserWidget* ActiveWidget = *ActiveWidgetPtr;
		if (UBaseScreen* ActiveScreen = Cast<UBaseScreen>(ActiveWidget))
		{
			UWidgetAnimation* ExitAnim = ActiveScreen->ExitScreenAnim;
			if (ExitAnim)
			{
				WidgetAnimFinishedEvent.BindDynamic(this, &UScreenManager::RemoveScreen);
				ActiveScreen->BindToAnimationFinished(ExitAnim, WidgetAnimFinishedEvent);
				ActiveScreen->PlayAnimation(ExitAnim);
			}
			else
			{
				RemoveScreen();
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UScreenManager::ExitScreen : Screen %d is not active"), static_cast<uint8>(InScreenToRemove));
	}
}

void UScreenManager::RemoveScreen()
{
	if (UUserWidget** ActiveWidgetPtr = ActiveScreensMap.Find(ScreenToRemove))
	{
		UUserWidget* ActiveWidget = *ActiveWidgetPtr;
		if (ActiveWidget)
		{
			ActiveWidget->RemoveFromParent();
			ActiveScreensMap.Remove(ScreenToRemove);
		}
	}

	if (ScreenToEnter != EScreenType::HUD)
	{
		EnterScreen(ScreenToEnter);
	}
	else
	{
		// TODO: logic for entering HUD and notifying HUD manager
	}
}
