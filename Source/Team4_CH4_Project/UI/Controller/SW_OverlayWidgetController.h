// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Controller/SW_WidgetController.h"
#include "AbilitySystemComponent.h"
#include "SW_OverlayWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnATChangedSignature, float, NewAT);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDFChangedSignature, float, NewDF);

UCLASS(BlueprintType, Blueprintable)
class TEAM4_CH4_PROJECT_API USW_OverlayWidgetController : public USW_WidgetController
{
	GENERATED_BODY()
public:
	virtual void BroadcastInitialValue() override;
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnATChangedSignature OnATChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnDFChangedSignature OnDFChanged;

protected:
	void ATChanged(const FOnAttributeChangeData& Data) const;
	void DFChanged(const FOnAttributeChangeData& Data) const;
};
