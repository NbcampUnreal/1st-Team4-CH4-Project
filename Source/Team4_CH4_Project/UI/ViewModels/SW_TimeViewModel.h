// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "SW_TimeViewModel.generated.h"

UCLASS()
class TEAM4_CH4_PROJECT_API USW_TimeViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure)
	int32 GetRemainingTimeSeconds() const { return RemainingTimeSeconds; };
	UFUNCTION(BlueprintCallable)
	void SetRemainingTimeSeconds(const int32& NewTimeSeconds);
	/*
	UFUNCTION(BlueprintPure, FieldNotify)
	FText GetRemainingTimeText() const;
	*/

private:
	UPROPERTY(BlueprintReadWrite, FieldNotify, Getter, Setter, meta = (AllowPrivateAccess))
	int32 RemainingTimeSeconds;
};
