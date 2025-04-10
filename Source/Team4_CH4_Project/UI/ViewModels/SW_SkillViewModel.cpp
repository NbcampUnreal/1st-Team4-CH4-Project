// Fill out your copyright notice in the Description page of Project Settings.

#include "SW_SkillViewModel.h"

void USW_SkillViewModel::SetSkill1Time(const float& DownTime)
{
	UE_MVVM_SET_PROPERTY_VALUE(Skill1Time, DownTime);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetSkill1Time);
}

void USW_SkillViewModel::SetSkill2Time(const float& DownTime)
{
	UE_MVVM_SET_PROPERTY_VALUE(Skill2Time, DownTime);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetSkill2Time);
}
void USW_SkillViewModel::SetSkill3Time(const float& DownTime)
{
	UE_MVVM_SET_PROPERTY_VALUE(Skill3Time, DownTime);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetSkill3Time);
}
void USW_SkillViewModel::SetDashTime(const float& DownTime)
{
	UE_MVVM_SET_PROPERTY_VALUE(DashTime, DownTime);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetDashTime);
}
