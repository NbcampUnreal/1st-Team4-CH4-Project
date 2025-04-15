// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_HPBarWidgetController.h"
#include "AbilitySystem/SW_AttributeSet.h"

void USW_HPBarWidgetController::BroadcastInitialValue()
{
	if (AttributeSet)
	{
		const USW_AttributeSet* AuraAttributeSet = CastChecked<USW_AttributeSet>(AttributeSet);
		OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth(), AuraAttributeSet->GetMaxHealth());
		OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetHealth(), AuraAttributeSet->GetMaxHealth());
	}
}

void USW_HPBarWidgetController::BindCallbacksToDependencies()
{
	if (AttributeSet)
	{
		const USW_AttributeSet* SW_AttributeSet = CastChecked<USW_AttributeSet>(AttributeSet);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(SW_AttributeSet->GetHealthAttribute()).AddUObject(this, &USW_HPBarWidgetController::HealthChanged);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(SW_AttributeSet->GetMaxHealthAttribute()).AddUObject(this, &USW_HPBarWidgetController::MaxHealthChanged);
	}
}

void USW_HPBarWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	float MaxHealth;
	if (AttributeSet)
	{
		const USW_AttributeSet* AuraAttributeSet = CastChecked<USW_AttributeSet>(AttributeSet);
		MaxHealth = AuraAttributeSet->GetMaxHealth();
	}
	OnHealthChanged.Broadcast(Data.NewValue, MaxHealth);
}

void USW_HPBarWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	float Health;
	if (AttributeSet)
	{
		const USW_AttributeSet* AuraAttributeSet = CastChecked<USW_AttributeSet>(AttributeSet);
		Health = AuraAttributeSet->GetHealth();
	}
	OnMaxHealthChanged.Broadcast(Health, Data.NewValue);
}