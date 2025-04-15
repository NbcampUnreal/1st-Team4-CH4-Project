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