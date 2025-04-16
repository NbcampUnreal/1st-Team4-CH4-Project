// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "../CharacterData/SW_CharacterType.h"
#include "SW_SkillViewModel.generated.h"

UCLASS()
class TEAM4_CH4_PROJECT_API USW_SkillViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, FieldNotify)
	ESkillType GetUsedSkillType() const { return UsedSkillType; };
	UFUNCTION(BlueprintCallable)
	void SetUsedSkillType(const ESkillType& SkillType);
	UFUNCTION(BlueprintPure, FieldNotify)
	float GetSkill1Time() const { return Skill1Time; };
	UFUNCTION(BlueprintCallable)
	void SetSkill1Time(const float& DownTime);
	UFUNCTION(BlueprintPure, FieldNotify)
	float GetSkill2Time() const { return Skill2Time; };
	UFUNCTION(BlueprintCallable)
	void SetSkill2Time(const float& DownTime);
	UFUNCTION(BlueprintPure, FieldNotify)
	float GetSkill3Time() const { return Skill3Time; };
	UFUNCTION(BlueprintCallable)
	void SetSkill3Time(const float& DownTime);
	UFUNCTION(BlueprintPure, FieldNotify)
	float GetDashTime() const { return DashTime; };
	UFUNCTION(BlueprintCallable)
	void SetDashTime(const float& DownTime);

	void ResetSkillTime(ESkillType Type);

private:
	UPROPERTY(BlueprintReadWrite, FieldNotify, Getter, Setter, meta = (AllowPrivateAccess))
	ESkillType UsedSkillType;
	UPROPERTY(BlueprintReadWrite, FieldNotify, Getter, Setter, meta = (AllowPrivateAccess))
	float Skill1Time;
	UPROPERTY(BlueprintReadWrite, FieldNotify, Getter, Setter, meta = (AllowPrivateAccess))
	float Skill2Time;
	UPROPERTY(BlueprintReadWrite, FieldNotify, Getter, Setter, meta = (AllowPrivateAccess))
	float Skill3Time;
	UPROPERTY(BlueprintReadWrite, FieldNotify, Getter, Setter, meta = (AllowPrivateAccess))
	float DashTime;
};
