// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_SettingsMenu.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/GameUserSettings.h"

void USW_SettingsMenu::NativeConstruct()
{
	Super::NativeConstruct();

	
	SetupSettings();

	if (ResPlusButton)
	{
		ResPlusButton->OnClicked.AddDynamic(this, &USW_SettingsMenu::IncrementResolution);
	}
	if (ResMinusButton)
	{
		ResMinusButton->OnClicked.AddDynamic(this, &USW_SettingsMenu::DecrementResolution);
	}
	if (ScreenButton)
	{
		ScreenButton->OnClicked.AddDynamic(this, &USW_SettingsMenu::ChangeScreenMode);
	}
	if (ApplyButton)
	{
		ApplyButton->OnClicked.AddDynamic(this, &USW_SettingsMenu::ApplyChanges);
	}
	if (ExitButton)
	{
		ExitButton->OnClicked.AddDynamic(this, &USW_SettingsMenu::ExitSettings);
	}
}

void USW_SettingsMenu::SetupSettings()
{
	UKismetSystemLibrary::GetSupportedFullscreenResolutions(Resolutions);
	Settings = GEngine->GetGameUserSettings();
	if (!IsValid(Settings)) return;

	for (int32 i = 0; i < Resolutions.Num(); ++i)
	{
		const FIntPoint& Resolution = Resolutions[i];
		FText ResolutionText = FText::FromString(
			FString::Printf(TEXT("%d X %d"), Resolution.X, Resolution.Y));
		ResolutionTexts.Add(ResolutionText);

		if (Resolution == Settings->GetScreenResolution() && ResText)
		{
			ResText->SetText(ResolutionText);
			CurrentResIndex = i;
		}
	}

	WindowMode = Settings->GetFullscreenMode();
	SetScreenModeText();
}

void USW_SettingsMenu::IncrementResolution()
{
	if (CurrentResIndex < Resolutions.Num() - 1)
	{
		CurrentResIndex++;
		UpdateResolution();
	}
}

void USW_SettingsMenu::DecrementResolution()
{
	if (CurrentResIndex > 0)
	{
		CurrentResIndex--;
		UpdateResolution();
	}
}

void USW_SettingsMenu::UpdateResolution()
{
	if (!IsValid(Settings)) return;

	if (ResText && ResolutionTexts.IsValidIndex(CurrentResIndex))
	{
		ResText->SetText(ResolutionTexts[CurrentResIndex]);
	}
	
	if (Resolutions.IsValidIndex(CurrentResIndex))
	{
		Settings->SetScreenResolution(Resolutions[CurrentResIndex]);
	}
}

void USW_SettingsMenu::SetScreenModeText()
{
	if (ScreenText)
	{
		switch (WindowMode)
		{
		case EWindowMode::Fullscreen:
			ScreenText->SetText(FText::FromString(TEXT("Fullscreen")));
			break;

		case EWindowMode::WindowedFullscreen:
			ScreenText->SetText(FText::FromString(TEXT("Windowed Fullscreen")));
			break;

		case EWindowMode::Windowed:
			ScreenText->SetText(FText::FromString(TEXT("Windowed")));
			break;
		}
	}
}

void USW_SettingsMenu::ChangeScreenMode()
{
	if (!IsValid(Settings)) return;

	if (ScreenText)
	{
		switch (WindowMode)
		{
		case EWindowMode::Fullscreen:
			WindowMode = EWindowMode::WindowedFullscreen;
			break;

		case EWindowMode::WindowedFullscreen:
			WindowMode = EWindowMode::Windowed;
			break;

		case EWindowMode::Windowed:
			WindowMode = EWindowMode::Fullscreen;
			break;
		}
	}

	Settings->SetFullscreenMode(WindowMode);
	SetScreenModeText();
}

void USW_SettingsMenu::ApplyChanges()
{
	if (IsValid(Settings))
	{
		Settings->ApplySettings(false);
	}
}

void USW_SettingsMenu::ExitSettings()
{
	if (IsValid(Settings))
	{
		Settings->ResetToCurrentSettings();
	}

	RemoveFromParent();
}
