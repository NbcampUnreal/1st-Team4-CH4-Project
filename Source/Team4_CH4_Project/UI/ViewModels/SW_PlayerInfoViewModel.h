// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "../CharacterData/SW_CharacterType.h"
#include "SW_PlayerInfoViewModel.generated.h"


UCLASS()
class TEAM4_CH4_PROJECT_API USW_PlayerInfoViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure)
	ECharacterType GetCharacterType() const { return CharacterType; };
	UFUNCTION(BlueprintCallable)
	void SetCharacterType(const ECharacterType& NewType);
	UFUNCTION(BlueprintPure)
	int32 GetLifeNum() const { return LifeNum; };
	UFUNCTION(BlueprintCallable)
	void SetLifeNum(const int32& NewLifeNum);
	UFUNCTION(BlueprintPure)
	int32 GetDamage() const { return Damage; };
	UFUNCTION(BlueprintCallable)
	void SetDamage(const int32& NewDamage);
	UFUNCTION(BlueprintPure, FieldNotify)
	FText GetDamageText() const { return FText::AsNumber(Damage); };
	UFUNCTION(BlueprintPure)
	int32 GetDefense() const { return Defense; };
	UFUNCTION(BlueprintCallable)
	void SetDefense(const int32& NewDefense);

	UFUNCTION(BlueprintPure, FieldNotify)
	FText GetDefenseText() const { return FText::AsNumber(Defense); };
	UFUNCTION(BlueprintPure)
	int32 GetSpeed() const { return Speed; };
	UFUNCTION(BlueprintCallable)
	void SetSpeed(const int32& NewSpeed);
	UFUNCTION(BlueprintPure, FieldNotify)
	FText GetSpeedText() const { return FText::AsNumber(Speed); };

private:
	UPROPERTY(BlueprintReadWrite, FieldNotify, Getter, Setter, meta = (AllowPrivateAccess))
	ECharacterType CharacterType;
	UPROPERTY(BlueprintReadWrite, FieldNotify, Getter, Setter, meta = (AllowPrivateAccess))
	int32 LifeNum;
	UPROPERTY(BlueprintReadWrite, FieldNotify, Getter, Setter, meta = (AllowPrivateAccess))
	int32 Damage;
	UPROPERTY(BlueprintReadWrite, FieldNotify, Getter, Setter, meta = (AllowPrivateAccess))
	int32 Defense;
	UPROPERTY(BlueprintReadWrite, FieldNotify, Getter, Setter, meta = (AllowPrivateAccess))
	int32 Speed;
};
