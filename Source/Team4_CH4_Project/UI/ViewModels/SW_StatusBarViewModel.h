// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "SW_StatusBarViewModel.generated.h"

UCLASS()
class TEAM4_CH4_PROJECT_API USW_StatusBarViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure)
	int32 GetMaxHealth() const { return MaxHealth; };
	UFUNCTION(BlueprintCallable)
	void SetMaxHealth(const int32& NewMaxHealth);
	UFUNCTION(BlueprintPure)
	int32 GetCurrentHealth() const { return CurrentHealth; };
	UFUNCTION(BlueprintCallable)
	void SetCurrentHealth(const int32& NewCurrentHealth);
	UFUNCTION(BlueprintPure, FieldNotify)
	float GetHealthPercent() const;

	UFUNCTION(BlueprintPure)
	int32 GetMaxStamina() const { return MaxStamina; };
	UFUNCTION(BlueprintCallable)
	void SetMaxStamina(const int32& NewMaxStamina);
	UFUNCTION(BlueprintPure)
	int32 GetCurrentStamina() const { return CurrentStamina; };
	UFUNCTION(BlueprintCallable)
	void SetCurrentStamina(const int32& NewCurrentStamina);
	UFUNCTION(BlueprintPure, FieldNotify)
	float GetStaminaPercent() const;

	UFUNCTION(BlueprintPure)
	FName GetUsername() const { return Username; };
	UFUNCTION(BlueprintCallable)
	void SetUsername(const FName& NewUsername);
	UFUNCTION(BlueprintPure, FieldNotify)
	FText GetUsernameText() const;

private:
	UPROPERTY(BlueprintReadWrite, FieldNotify, Getter, Setter, meta = (AllowPrivateAccess))
	int32 CurrentHealth;
	UPROPERTY(BlueprintReadWrite, FieldNotify, Getter, Setter, meta = (AllowPrivateAccess))
	int32 MaxHealth;
	UPROPERTY(BlueprintReadWrite, FieldNotify, Getter, Setter, meta = (AllowPrivateAccess))
	int32 CurrentStamina;
	UPROPERTY(BlueprintReadWrite, FieldNotify, Getter, Setter, meta = (AllowPrivateAccess))
	int32 MaxStamina;
	UPROPERTY(BlueprintReadWrite, FieldNotify, Getter, Setter, meta = (AllowPrivateAccess))
	FName Username;

};
