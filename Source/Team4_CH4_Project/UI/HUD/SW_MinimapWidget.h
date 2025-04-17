// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SW_MinimapWidget.generated.h"

class UImage;

UCLASS()
class TEAM4_CH4_PROJECT_API USW_MinimapWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* MinimapImage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* PlayerMarker;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Minimap")
	float CaptureOffsetX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Minimap")
	float CaptureOffsetY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Minimap")
	float MinimapSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Minimap")
	UMaterialParameterCollection* MPCMinimap;

	USW_MinimapWidget(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable)
	void UpdateMinimap();
};
