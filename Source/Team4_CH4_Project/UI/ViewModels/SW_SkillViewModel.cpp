// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_SkillViewModel.h"


void USW_SkillViewModel::SetSkill1Time(const float& RemainingTime)
{
	UE_MVVM_SET_PROPERTY_VALUE(Skill1Time, RemainingTime);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetSkill1Time);
}