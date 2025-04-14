// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Controller/SW_WidgetController.h"
#include "AbilitySystemComponent.h"
#include "SW_HPBarWidgetController.generated.h"

UCLASS()
class TEAM4_CH4_PROJECT_API USW_HPBarWidgetController : public USW_WidgetController
{
	GENERATED_BODY()
public:
	virtual void BroadcastInitialValue() override;
	virtual void BindCallbacksToDependencies() override;

	UFUNCTION(BlueprintCallable, Category = "Attribute")
	float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = "Attribute")
	float GetMaxHealth() const;

protected:
	void OnHealthChanged(const FOnAttributeChangeData& Data);
};
