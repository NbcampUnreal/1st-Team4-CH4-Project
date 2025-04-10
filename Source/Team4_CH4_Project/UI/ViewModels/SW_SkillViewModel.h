// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "SW_SkillViewModel.generated.h"

UCLASS()
class TEAM4_CH4_PROJECT_API USW_SkillViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, FieldNotify)
	float GetSkill1Time() const { return Skill1Time; };
	UFUNCTION(BlueprintCallable)
	void SetSkill1Time(const float& RemainingTime);

private:
	UPROPERTY(BlueprintReadWrite, FieldNotify, Getter, Setter, meta = (AllowPrivateAccess))
	float Skill1Time;

};
