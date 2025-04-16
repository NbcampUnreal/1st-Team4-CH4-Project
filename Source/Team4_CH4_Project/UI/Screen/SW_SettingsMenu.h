// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SW_SettingsMenu.generated.h"

class UTextBlock;
class UButton;

UCLASS(meta = (DisableNativeTick))
class TEAM4_CH4_PROJECT_API USW_SettingsMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ResText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ScreenText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* ResMinusButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* ResPlusButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* ScreenButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* ApplyButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* ExitButton;
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* EnterAnim;

	UPROPERTY(BlueprintReadWrite)
	TArray<FIntPoint> Resolutions;
	UPROPERTY(BlueprintReadWrite)
	TArray<FText> ResolutionTexts;
	UPROPERTY(BlueprintReadWrite)
	int32 CurrentResIndex;
	UPROPERTY(BlueprintReadWrite)
	TEnumAsByte<EWindowMode::Type> WindowMode;

	UPROPERTY(BlueprintReadWrite)
	UGameUserSettings* Settings;

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void SetupSettings();

	UFUNCTION(BlueprintCallable)
	void IncrementResolution();
	UFUNCTION(BlueprintCallable)
	void DecrementResolution();
	UFUNCTION(BlueprintCallable)
	void UpdateResolution();

	UFUNCTION(BlueprintCallable)
	void SetScreenModeText();
	UFUNCTION(BlueprintCallable)
	void ChangeScreenMode();

	UFUNCTION(BlueprintCallable)
	void ApplyChanges();
	UFUNCTION(BlueprintCallable)
	void ExitSettings();
};
