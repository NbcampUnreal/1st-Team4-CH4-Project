// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_AttributeSet.h"
#include "Net/UnrealNetwork.h"

USW_AttributeSet::USW_AttributeSet()
{
	InitHealth(50.f);
	InitMaxHealth(100.f);
	InitMana(50.f);
	InitMaxMana(50.f);
	InitAT(456.f);
	InitDF(321.f);
	InitH_DownTime(3.f);
	InitJ_DownTime(10.f);
}

void USW_AttributeSet::OnRep_Health(const FGameplayAttributeData& Old_Health) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USW_AttributeSet, Health, Old_Health);
}

void USW_AttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& Old_MaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USW_AttributeSet, MaxHealth, Old_MaxHealth);
}

void USW_AttributeSet::OnRep_Mana(const FGameplayAttributeData& Old_Mana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USW_AttributeSet, Mana, Old_Mana);
}

void USW_AttributeSet::OnRep_MaxMana(const FGameplayAttributeData& Old_MaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USW_AttributeSet, MaxMana, Old_MaxMana);
}

void USW_AttributeSet::OnRep_AT(const FGameplayAttributeData& Old_AT) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USW_AttributeSet, AT, Old_AT);
}

void USW_AttributeSet::OnRep_DF(const FGameplayAttributeData& Old_DF) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USW_AttributeSet, DF, Old_DF);
}

void USW_AttributeSet::OnRep_H_DownTime(const FGameplayAttributeData& Old_Q_DownTime) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USW_AttributeSet, H_DownTime, Old_Q_DownTime);
}

void USW_AttributeSet::OnRep_J_DownTime(const FGameplayAttributeData& Old_R_DownTime) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USW_AttributeSet, J_DownTime, Old_R_DownTime);
}



void USW_AttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(USW_AttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USW_AttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USW_AttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USW_AttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USW_AttributeSet, AT, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USW_AttributeSet, DF, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USW_AttributeSet, H_DownTime, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USW_AttributeSet, J_DownTime, COND_None, REPNOTIFY_Always);
}
