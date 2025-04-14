// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SW_UserWidget.generated.h"

class USW_WidgetController;
class UAbilitySystemComponent;
class UAttributeSet;
struct FWidgetControllerParams;

UCLASS()
class TEAM4_CH4_PROJECT_API USW_UserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(USW_WidgetController* InWidgetController);

	//UFUNCTION()
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<USW_WidgetController> WidgetController;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
};
