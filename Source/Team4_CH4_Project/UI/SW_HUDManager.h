// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "CharacterData/SW_CharacterType.h"
#include "CharacterData/SW_CharacterDataRow.h"
#include "CharacterData/SW_SkillDataRow.h"
#include "SW_HUDManager.generated.h"

UENUM(BlueprintType)
enum class EViewModelType : uint8
{
	StatusBarViewModel		UMETA(DisplayName="StatusBar"),
	PlayerInfoViewModel		UMETA(DisplayName="PlayerInfo"),
	SkillViewModel			UMETA(DisplayName="Skill"),
	LevelExpViewModel		UMETA(DisplayName="LevelEXP"),
	DebuffViewModel			UMETA(DisplayName="Debuff"),
	SquadViewModel			UMETA(DisplayName="Squad"),
	TimeViewModel			UMETA(DisplayName="Time"),
	MAX						UMETA(DisplayName="MAX")
};

class UMVVMViewModelBase;

UCLASS()
class TEAM4_CH4_PROJECT_API USW_HUDManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	/*** HUD ***/
	// HUD Widget class pointer (soft) and asset path
	UPROPERTY()
	TSoftClassPtr<UUserWidget> HUDWidgetClassPtr;
	FSoftObjectPath HUDWidgetClassPath;

	// HUD control methods
	UFUNCTION(BlueprintCallable)
	void InitializeHUD();
	UFUNCTION(BlueprintCallable)
	void DisplayHUD();
	UFUNCTION(BlueprintCallable)
	void HideHUD();
	UFUNCTION(BlueprintCallable)
	void RemoveHUD();
	UFUNCTION(BlueprintCallable)
	UUserWidget* GetHUDWidget();

	/*** Data Table ***/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterData")
	UDataTable* CharacterDataTable;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterData")
	UDataTable* SkillDataTable;

	UFUNCTION(BlueprintCallable)
	FCharacterDataRow GetCharacterData(ECharacterType CharacterType);
	UFUNCTION(BlueprintCallable)
	FSkillDataRow GetSkillData(ECharacterType CharacterType);

	/*** ViewModel ***/
	// ViewModel control methods
	UFUNCTION(BlueprintCallable)
	void InitializeAllViewModels();
	UFUNCTION(BlueprintCallable)
	void InitializeViewModel(EViewModelType ViewModelType);
	UFUNCTION(BlueprintCallable)
	void RemoveAllViewModels();
	UFUNCTION(BlueprintCallable)
	void RemoveViewModel(EViewModelType ViewModelType);
	UFUNCTION(BlueprintCallable)
	UMVVMViewModelBase* GetViewModel(EViewModelType ViewModelType);
	
protected:
	UPROPERTY()
	UUserWidget* HUDWidget;
	UPROPERTY()
	TMap<EViewModelType, UMVVMViewModelBase*> ViewModelMap;
};
