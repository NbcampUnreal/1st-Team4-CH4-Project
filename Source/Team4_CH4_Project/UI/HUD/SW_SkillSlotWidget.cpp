// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_SkillSlotWidget.h"
#include "SW_SkillWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void USW_SkillSlotWidget::SetSkillIcons(ECharacterType Type)
{
	if (UGameInstance* GameInstance = GetGameInstance())
	{
		if (USW_HUDManager* HUDManager = GameInstance->GetSubsystem<USW_HUDManager>())
		{
			FSkillDataRow SkillData = HUDManager->GetSkillData(Type);

			if (AttackWidget && IsValid(SkillData.AttackIcon))
			{
				AttackWidget->SetSkillIcon(SkillData.AttackIcon);
				AttackWidget->SetInputText(FText::FromString(TEXT("U")));
			}
			/*
			if (GuardWidget && IsValid(SkillData.GuardIcon))
			{
				GuardWidget->SetSkillIcon(SkillData.GuardIcon);
			}
			*/

			if (DashWidget && IsValid(SkillData.DashIcon))
			{
				DashWidget->SetSkillIcon(SkillData.DashIcon);
				DashWidget->SetInputText(FText::FromString(TEXT("I")));
			}

			if (Skill1Widget && IsValid(SkillData.Skill1Icon))
			{
				Skill1Widget->SetSkillIcon(SkillData.Skill1Icon);
				Skill1Widget->SetInputText(FText::FromString(TEXT("H")));
			}

			if (Skill2Widget && IsValid(SkillData.Skill2Icon))
			{
				Skill2Widget->SetSkillIcon(SkillData.Skill2Icon);
				Skill2Widget->SetInputText(FText::FromString(TEXT("J")));
			}
			/*
			if (Skill3Widget && IsValid(SkillData.Skill3Icon))
			{
				Skill3Widget->SetSkillIcon(SkillData.Skill3Icon);
			}
			*/
		}
	}
}

void USW_SkillSlotWidget::StartDashDown(const float& DownTime)
{
	if (DashWidget && DownTime > 0.f)
	{
		DashWidget->StartSkillTimer(DownTime);
	}
}

void USW_SkillSlotWidget::StartSkill1Down(const float& DownTime)
{
	if (Skill1Widget && DownTime > 0.f)
	{
		Skill1Widget->StartSkillTimer(DownTime);
	}
}

void USW_SkillSlotWidget::StartSkill2Down(const float& DownTime)
{
	if (Skill2Widget && DownTime > 0.f)
	{
		Skill2Widget->StartSkillTimer(DownTime);
	}
}

void USW_SkillSlotWidget::StartSkill3Down(const float& DownTime)
{
	if (Skill3Widget && DownTime > 0.f)
	{
		Skill3Widget->StartSkillTimer(DownTime);
	}
}
