// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Controller/SW_WidgetController.h"
#include "AbilitySystemComponent.h"
#include "SW_HPBarWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChangedSignature, float, NewHealth, float, OldMaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMaxHealthChangedSignature, float, NewMaxHealth, float, OldHealth);

//  DelegateName, Param1Type, Param1Name, Param2Type, Param2Name
UCLASS(BlueprintType, Blueprintable)
class TEAM4_CH4_PROJECT_API USW_HPBarWidgetController : public USW_WidgetController
{
	GENERATED_BODY()
public:
	virtual void BroadcastInitialValue() override;
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnHealthChangedSignature OnHealthChanged;
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnMaxHealthChangedSignature OnMaxHealthChanged;

protected:

	void HealthChanged(const FOnAttributeChangeData& Data) const;
	void MaxHealthChanged(const FOnAttributeChangeData& Data) const;
};
