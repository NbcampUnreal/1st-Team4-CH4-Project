// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../CharacterData/SW_CharacterType.h"
#include "SW_PlayerInfoWidget.generated.h"

class UImage;
class UTextBlock;
class UProgressBar;
class UHorizontalBox;

UCLASS()
class TEAM4_CH4_PROJECT_API USW_PlayerInfoWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	virtual void SetThumbnailByType(ECharacterType Type);

	UFUNCTION(BlueprintCallable)
	void UpdateLifeIcons(int32 LifeNum);

protected:
	/* Under the left Vertical Box */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* PlayerThumbnail;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetOptional))
	UTextBlock* PlayerLevelText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetOptional))
	UProgressBar* ExpBar;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetOptional))
	UHorizontalBox* DebuffHBox;
	
	/* Under the right Vertical Box */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetOptional))
	UHorizontalBox* LifeHBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetOptional))
	UTextBlock* DamageText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetOptional))
	UTextBlock* DefenseText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetOptional))
	UTextBlock* SpeedText;

	int32 RemainingLives;
};
