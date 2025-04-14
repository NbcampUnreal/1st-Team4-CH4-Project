// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_WidgetController.h"

void USW_WidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

void USW_WidgetController::BroadcastInitialValue()
{

}

void USW_WidgetController::BindCallbacksToDependencies()
{
}
