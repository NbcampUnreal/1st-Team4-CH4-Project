// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SW_TimeWidget.generated.h"

class UMVVMViewModelBase;

UCLASS()
class TEAM4_CH4_PROJECT_API USW_TimeWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetViewModel(UMVVMViewModelBase* InViewModel);
private:
	UMVVMViewModelBase* ViewModel;
};
