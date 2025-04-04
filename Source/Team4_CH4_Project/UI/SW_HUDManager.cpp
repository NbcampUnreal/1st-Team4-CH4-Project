// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_HUDManager.h"
#include "Blueprint/UserWidget.h"
#include "ViewModels/SW_TimeViewModel.h"

void USW_HUDManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	HUDWidgetClassPath.SetPath(TEXT("/Game/UI/HUD/WBP/WBP_MainHUDWidget.WBP_MainHUDWidget_C"));
	HUDWidgetClassPtr = TSoftClassPtr<UUserWidget>(HUDWidgetClassPath);
}

void USW_HUDManager::DisplayHUD()
{
	InitializeViewModels();

	if (!HUDWidget)
	{
		if (UClass* LoadedHUDWidgetClass = HUDWidgetClassPtr.LoadSynchronous())
		{
			HUDWidget = CreateWidget<UUserWidget>(GetWorld()->GetFirstPlayerController(), LoadedHUDWidgetClass, TEXT("HUDWidget"));
		}
	}

	if (IsValid(HUDWidget))
	{
		HUDWidget->AddToViewport();
		HUDWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
}

void USW_HUDManager::HideHUD()
{
	if (IsValid(HUDWidget))
	{
		HUDWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void USW_HUDManager::RemoveHUD()
{
	if (IsValid(HUDWidget))
	{
		HUDWidget->RemoveFromParent();
		HUDWidget = nullptr;
	}

	RemoveAllViewModels();
}

UUserWidget* USW_HUDManager::GetHUDWidget()
{
	return IsValid(HUDWidget) ? HUDWidget : nullptr;
}

void USW_HUDManager::InitializeViewModels()
{
	if (!ViewModelMap.Find(EViewModelType::TimeViewModel))
	{
		UMVVMViewModelBase* TimeViewModel = NewObject<USW_TimeViewModel>(this);
		ViewModelMap.Add(EViewModelType::TimeViewModel, TimeViewModel);
	}
}

UMVVMViewModelBase* USW_HUDManager::GetViewModel(EViewModelType ViewModelType)
{
	UMVVMViewModelBase** ViewModelPtr = ViewModelMap.Find(ViewModelType);
	return ViewModelPtr ? *ViewModelPtr : nullptr;
}

void USW_HUDManager::RemoveViewModel(EViewModelType ViewModelType)
{
	UMVVMViewModelBase* ViewModel = nullptr;
	if (ViewModelMap.RemoveAndCopyValue(ViewModelType, ViewModel))
	{
		if (!ViewModel->IsPendingKillEnabled())
		{
			ViewModel->ConditionalBeginDestroy();
		}
	}
}

void USW_HUDManager::RemoveAllViewModels()
{
	for (int32 i = 0; i < static_cast<int32>(EViewModelType::MAX); ++i)
	{
		EViewModelType ViewModelType = static_cast<EViewModelType>(i);
		RemoveViewModel(ViewModelType);
	}
}
