// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widget/SW_UserWidget.h"
#include "SW_PlayerStatWidget.generated.h"

class UImage;
class UTextBlock;
class UProgressBar;
class UHorizontalBox;

UCLASS()
class TEAM4_CH4_PROJECT_API USW_PlayerStatWidget : public USW_UserWidget
{
	GENERATED_BODY()
protected:
	/* Under the left Vertical Box */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* PlayerThumbnail;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* PlayerLevelText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* ExpBar;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UHorizontalBox* DebuffHBox;

	/* Under the right Vertical Box */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UHorizontalBox* LifeHBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ATText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* DFText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* AGIText;
};
