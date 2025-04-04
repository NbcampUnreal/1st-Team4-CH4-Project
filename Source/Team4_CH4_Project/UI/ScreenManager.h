// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Blueprint/UserWidget.h"
#include "ScreenManager.generated.h"

UENUM(BlueprintType)
enum class EScreenType : uint8
{
	TitleScreen		UMETA(DisplayName = "TitleScreen"),
	SettingsMenu	UMETA(DisplayName = "SettingsMenu"),
	LobbyScreen		UMETA(DisplayName = "LobbyScreen"),
	LoadingScreen	UMETA(DisplayName = "LoadingScreen"),
	IngameMenu		UMETA(DisplayName = "IngameMenu"),
	ResultsScreen	UMETA(DisplayName = "ResultsScreen"),
	HUD				UMETA(DisplayName = "HUD"),
	MAX				UMETA(DisplayName = "MAX")
};

UCLASS()
class TEAM4_CH4_PROJECT_API UScreenManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void EnterScreen(EScreenType ScreenType);
	UFUNCTION(BlueprintCallable)
	void ExitScreen(EScreenType InScreenToRemove, EScreenType InScreenToEnter);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ScreenWidgets")
	TMap<EScreenType, TSubclassOf<UUserWidget>> ScreenClassMap;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ScreenWidgets")
	TMap<EScreenType, UUserWidget*> ActiveScreensMap;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ScreenWidgets")
	EScreenType ScreenToRemove;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ScreenWidgets")
	EScreenType ScreenToEnter;


	FWidgetAnimationDynamicEvent WidgetAnimFinishedEvent;

	UFUNCTION()
	void RemoveScreen();
};
