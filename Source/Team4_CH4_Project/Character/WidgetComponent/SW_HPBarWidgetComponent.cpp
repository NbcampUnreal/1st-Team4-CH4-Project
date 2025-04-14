// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_HPBarWidgetComponent.h"
#include "AbilitySystem/SW_AbilitySystemComponent.h"
#include "AbilitySystem/SW_AttributeSet.h"

USW_HPBarWidgetComponent::USW_HPBarWidgetComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USW_HPBarWidgetComponent::BeginPlay()
{
	Super::BeginPlay();
}

void USW_HPBarWidgetComponent::SetASC(USW_AbilitySystemComponent* _ASC, USW_AttributeSet* _AS)
{
	ASC = _ASC;
	AS = _AS;

	if (ASC && AS)
	{
		//ASC->GetGameplayAttributeValueChangeDelegate(AS->GetHealthAttribute()).AddUObject(this, &USW_HPBarWidget::UpdateHealthBar);
	}
}