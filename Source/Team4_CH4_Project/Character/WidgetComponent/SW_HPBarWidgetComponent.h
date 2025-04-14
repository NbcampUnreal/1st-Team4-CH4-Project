// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "SW_HPBarWidgetComponent.generated.h"

class USW_AbilitySystemComponent;
class USW_AttributeSet;
class USW_HPBarWidget;

UCLASS()
class TEAM4_CH4_PROJECT_API USW_HPBarWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
public:
	USW_HPBarWidgetComponent();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	USW_AbilitySystemComponent* ASC;

	UPROPERTY()
	USW_AttributeSet* AS;

public:
	UFUNCTION()
	void SetASC(USW_AbilitySystemComponent* _ASC, USW_AttributeSet* _AS);
};
