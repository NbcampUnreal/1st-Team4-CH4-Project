// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_HUDManager.h"
#include "Blueprint/UserWidget.h"
#include "ViewModels/SW_StatusBarViewModel.h"
#include "ViewModels/SW_TimeViewModel.h"
#include "ViewModels/SW_PlayerInfoViewModel.h"
#include "ViewModels/SW_LevelExpViewModel.h"
#include "ViewModels/SW_DebuffViewModel.h"
#include "ViewModels/SW_SquadViewModel.h"
#include "ViewModels/SW_SkillViewModel.h"
#include "CharacterData/SW_CharacterDataRow.h"

void USW_HUDManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	HUDWidgetClassPath.SetPath(TEXT("/Game/UI/HUD/WBP/WBP_MainHUDWidget.WBP_MainHUDWidget_C"));
	HUDWidgetClassPtr = TSoftClassPtr<UUserWidget>(HUDWidgetClassPath);
	
	FSoftObjectPath CharacterTablePath(TEXT("/Game/UI/CharacterData/DT_CharacterData.DT_CharacterData"));
	CharacterDataTable = Cast<UDataTable>(CharacterTablePath.TryLoad());

	FSoftObjectPath SkillTablePath(TEXT("/Game/UI/CharacterData/DT_SkillData.DT_SkillData"));
	SkillDataTable = Cast<UDataTable>(SkillTablePath.TryLoad());
}

void USW_HUDManager::InitializeHUD()
{
	InitializeAllViewModels();
	if (!HUDWidget)
	{
		if (UClass* LoadedHUDWidgetClass = HUDWidgetClassPtr.LoadSynchronous())
		{
			HUDWidget = CreateWidget<UUserWidget>(GetGameInstance(), LoadedHUDWidgetClass, TEXT("HUDWidget"));
		}
	}

	// Initialize Level and Exp values
	if (USW_LevelExpViewModel* LevelExpViewModel = Cast<USW_LevelExpViewModel>(GetViewModel(EViewModelType::PlayerInfoViewModel)))
	{
		LevelExpViewModel->SetCurrentExp(0);
		LevelExpViewModel->SetMaxExp(100);
		LevelExpViewModel->SetCurrentLevel(1);
	}
}

void USW_HUDManager::DisplayHUD()
{
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

FCharacterDataRow USW_HUDManager::GetCharacterData(ECharacterType CharacterType)
{
	if (IsValid(CharacterDataTable))
	{
		FName RowName = FName(UEnum::GetDisplayValueAsText(CharacterType).ToString());
		if (FCharacterDataRow* Row = CharacterDataTable->FindRow<FCharacterDataRow>(RowName, TEXT("HUD")))
		{
			return *Row;
		}
	}
	return FCharacterDataRow();
}

FSkillDataRow USW_HUDManager::GetSkillData(ECharacterType CharacterType)
{
	if (IsValid(SkillDataTable))
	{
		FName RowName = FName(UEnum::GetDisplayValueAsText(CharacterType).ToString());
		if (FSkillDataRow* Row = SkillDataTable->FindRow<FSkillDataRow>(RowName, TEXT("HUD")))
		{
			return *Row;
		}
	}
	return FSkillDataRow();
}

void USW_HUDManager::InitializeAllViewModels()
{
	for (int32 i = 0; i < static_cast<int32>(EViewModelType::MAX); ++i)
	{
		EViewModelType ViewModelType = static_cast<EViewModelType>(i);
		InitializeViewModel(ViewModelType);
	}
}

void USW_HUDManager::InitializeViewModel(EViewModelType ViewModelType)
{
	if (!ViewModelMap.Find(ViewModelType))
	{
		UMVVMViewModelBase* ViewModel = nullptr;
		switch (ViewModelType)
		{
		case EViewModelType::StatusBarViewModel:
			ViewModel = NewObject<USW_StatusBarViewModel>(this);
			break;
		case EViewModelType::PlayerInfoViewModel:
			ViewModel = NewObject<USW_PlayerInfoViewModel>(this);
			break;
		case EViewModelType::LevelExpViewModel:
			ViewModel = NewObject<USW_LevelExpViewModel>(this);
			break;
		case EViewModelType::DebuffViewModel:
			ViewModel = NewObject<USW_DebuffViewModel>(this);
			break;
		case EViewModelType::SquadViewModel:
			ViewModel = NewObject<USW_SquadViewModel>(this);
			break;
		case EViewModelType::TimeViewModel:
			ViewModel = NewObject<USW_TimeViewModel>(this);
			break;
		case EViewModelType::SkillViewModel:
			ViewModel = NewObject<USW_SkillViewModel>(this);
			break;
		//...
		}
		ViewModelMap.Add(ViewModelType, ViewModel);
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

void USW_HUDManager::RemoveViewModel(EViewModelType ViewModelType)
{
	UMVVMViewModelBase* ViewModel = nullptr;
	if (ViewModelMap.RemoveAndCopyValue(ViewModelType, ViewModel))
	{
		if (!ViewModel->IsGarbageEliminationEnabled())
		{
			ViewModel->ConditionalBeginDestroy();
		}
	}
}

UMVVMViewModelBase* USW_HUDManager::GetViewModel(EViewModelType ViewModelType)
{
	UMVVMViewModelBase** ViewModelPtr = ViewModelMap.Find(ViewModelType);
	return ViewModelPtr ? *ViewModelPtr : nullptr;
}
