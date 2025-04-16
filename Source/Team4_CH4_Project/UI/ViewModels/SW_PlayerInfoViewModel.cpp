// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_PlayerInfoViewModel.h"
#include "../CharacterData/SW_CharacterDataRow.h"
#include "../SW_HUDManager.h"

void USW_PlayerInfoViewModel::SetCharacterType(const ECharacterType& NewType)
{
	if (NewType < ECharacterType::MAX && NewType > ECharacterType::START)
	{
		if (UE_MVVM_SET_PROPERTY_VALUE(CharacterType, NewType))
		{
			if (USW_HUDManager* HUDManager = Cast<USW_HUDManager>(GetOuter()))
			{
				FCharacterDataRow Data = HUDManager->GetCharacterData(NewType);
				SetDamage(Data.Damage);
				SetDefense(Data.Defense);
				SetSpeed(Data.Speed);
			}
		}
	}
}

void USW_PlayerInfoViewModel::SetLifeNum(const int32& NewLifeNum)
{
	if (NewLifeNum > 0 /* && NewLifeNum < MaxLifeNum */)
	{
		UE_MVVM_SET_PROPERTY_VALUE(LifeNum, NewLifeNum);
	}
}

void USW_PlayerInfoViewModel::SetDamage(const int32& NewDamage)
{
	if (NewDamage > 0)
	{
		if (UE_MVVM_SET_PROPERTY_VALUE(Damage, NewDamage))
		{
			UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetDamageText);
		}
	}
}

void USW_PlayerInfoViewModel::SetDefense(const int32& NewDefense)
{
	if (NewDefense > 0)
	{
		if (UE_MVVM_SET_PROPERTY_VALUE(Defense, NewDefense))
		{
			UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetDefenseText);
		}
	}
}

void USW_PlayerInfoViewModel::SetSpeed(const int32& NewSpeed)
{
	if (NewSpeed > 0)
	{
		if (UE_MVVM_SET_PROPERTY_VALUE(Speed, NewSpeed))
		{
			UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetSpeedText);
		}
	}
}
