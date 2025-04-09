// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "SW_LevelExpViewModel.generated.h"

UCLASS()
class TEAM4_CH4_PROJECT_API USW_LevelExpViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure)
	int32 GetMaxExp() const { return MaxExp; };
	UFUNCTION(BlueprintCallable)
	void SetMaxExp(const int32& NewMaxExp);
	UFUNCTION(BlueprintPure)
	int32 GetCurrentExp() const { return CurrentExp; };
	UFUNCTION(BlueprintCallable)
	void SetCurrentExp(const int32& NewCurrentExp);
	UFUNCTION(BlueprintPure, FieldNotify)
	float GetExpPercent() const;

	UFUNCTION(BlueprintPure)
	int32 GetCurrentLevel() const { return CurrentLevel; };
	UFUNCTION(BlueprintCallable)
	void SetCurrentLevel(const int32& NewCurrentLevel);
	UFUNCTION(BlueprintPure, FieldNotify)
	FText GetCurrentLevelText() const;

private:
	UPROPERTY(BlueprintReadWrite, FieldNotify, Getter, Setter, meta = (AllowPrivateAccess))
	int32 CurrentExp;
	UPROPERTY(BlueprintReadWrite, FieldNotify, Getter, Setter, meta = (AllowPrivateAccess))
	int32 MaxExp;
	UPROPERTY(BlueprintReadWrite, FieldNotify, Getter, Setter, meta = (AllowPrivateAccess))
	int32 CurrentLevel;
};
