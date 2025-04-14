// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SW_HUD.generated.h"

class USW_OverlayWidgetController;
class UAbilitySystemComponent;
class UAttributeSet;
class USW_UserWidget;
struct FWidgetControllerParams;

UCLASS()
class TEAM4_CH4_PROJECT_API ASW_HUD : public AHUD
{
	GENERATED_BODY()
public:
	UPROPERTY()
	TObjectPtr<USW_UserWidget> OverlayWidget;

	USW_OverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);

	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

private:
	UPROPERTY()
	TObjectPtr<USW_OverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<USW_UserWidget> OverlayWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<USW_OverlayWidgetController> OverlayWidgetControllerClass;
};
