// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SW_HUDManager.generated.h"

UENUM(BlueprintType)
enum class EViewModelType : uint8
{
	StatusBarViewModel		UMETA(DisplayName="StatusBar"),
	PlayerStatViewModel		UMETA(DisplayName="PlayerStat"),
	LevelExpViewModel		UMETA(DisplayName="LevelEXP"),
	DebuffViewModel			UMETA(DisplayName="Debuff"),
	SquadViewModel			UMETA(DisplayName="Squad"),
	TimeViewModel			UMETA(DisplayName="Time"),
	MAX						UMETA(DisplayName="MAX")
};

class UMVVMViewModelBase;

UCLASS(Blueprintable)
class TEAM4_CH4_PROJECT_API USW_HUDManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UPROPERTY(EditDefaultsOnly, Category="HUD")
	TSoftClassPtr<UUserWidget> HUDWidgetClassPtr;

	FSoftObjectPath HUDWidgetClassPath;

	UFUNCTION(BlueprintCallable)
	void DisplayHUD();
	UFUNCTION(BlueprintCallable)
	void HideHUD();
	UFUNCTION(BlueprintCallable)
	void RemoveHUD();
	UFUNCTION(BlueprintCallable)
	UUserWidget* GetHUDWidget();

	UFUNCTION(BlueprintCallable)
	void InitializeViewModels();
	UFUNCTION(BlueprintCallable)
	UMVVMViewModelBase* GetViewModel(EViewModelType ViewModelType);
	UFUNCTION(BlueprintCallable)
	void RemoveViewModel(EViewModelType ViewModelType);
	UFUNCTION(BlueprintCallable)
	void RemoveAllViewModels();
	
protected:
	TMap<EViewModelType, UMVVMViewModelBase*> ViewModelMap;
	UUserWidget* HUDWidget;
};
