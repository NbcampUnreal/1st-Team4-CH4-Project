// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_HPBarWidgetController.h"
#include "AbilitySystem/SW_AttributeSet.h"

void USW_HPBarWidgetController::BroadcastInitialValue()
{
}

void USW_HPBarWidgetController::BindCallbacksToDependencies()
{
}

float USW_HPBarWidgetController::GetHealth() const
{
	const USW_AttributeSet* AS = Cast<USW_AttributeSet>(AttributeSet);
	return IsValid(AS) ? AS->GetHealth() : 0.f;
}

float USW_HPBarWidgetController::GetMaxHealth() const
{
	const USW_AttributeSet* AS = Cast<USW_AttributeSet>(AttributeSet);
	return IsValid(AS) ? AS->GetMaxHealth() : 0.f;
}

void USW_HPBarWidgetController::OnHealthChanged(const FOnAttributeChangeData& Data)
{
}
