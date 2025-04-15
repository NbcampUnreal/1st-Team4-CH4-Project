// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widget/SW_UserWidget.h"
//#include "Components/ProgressBar.h"
#include "SW_HPBarWidget.generated.h"

class UProgressBar;

UCLASS()
class TEAM4_CH4_PROJECT_API USW_HPBarWidget : public USW_UserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HPProgressBar;

public:
	virtual void NativeConstruct() override;

	virtual void NativeOnInitialized() override;	

	UFUNCTION()
	void ChangePercent(float _Health, float _MaxHealth);


};

