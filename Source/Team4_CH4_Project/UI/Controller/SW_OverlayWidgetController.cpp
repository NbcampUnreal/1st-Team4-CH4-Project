// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_OverlayWidgetController.h"
#include "AbilitySystem/SW_AttributeSet.h"

void USW_OverlayWidgetController::BroadcastInitialValue()
{
	if (AttributeSet)
	{
		const USW_AttributeSet* SW_AttributeSet = CastChecked<USW_AttributeSet>(AttributeSet);

		OnATChanged.Broadcast(SW_AttributeSet->GetAT());
		OnDFChanged.Broadcast(SW_AttributeSet->GetDF());
	}
}

void USW_OverlayWidgetController::BindCallbacksToDependencies()
{
	if (AttributeSet)
	{
		const USW_AttributeSet* SW_AttributeSet = CastChecked<USW_AttributeSet>(AttributeSet);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(SW_AttributeSet->GetATAttribute()).AddUObject(this, &USW_OverlayWidgetController::ATChanged);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(SW_AttributeSet->GetDFAttribute()).AddUObject(this, &USW_OverlayWidgetController::DFChanged);
	}
}

void USW_OverlayWidgetController::ATChanged(const FOnAttributeChangeData& Data) const
{
	OnATChanged.Broadcast(Data.NewValue);
}

void USW_OverlayWidgetController::DFChanged(const FOnAttributeChangeData& Data) const
{
	OnDFChanged.Broadcast(Data.NewValue);
}
