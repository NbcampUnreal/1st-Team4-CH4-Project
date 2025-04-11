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
			}

			if (GuardWidget && IsValid(SkillData.GuardIcon))
			{
				GuardWidget->SetSkillIcon(SkillData.GuardIcon);
			}

			if (DashWidget && IsValid(SkillData.DashIcon))
			{
				DashWidget->SetSkillIcon(SkillData.DashIcon);
			}

			if (Skill1Widget && IsValid(SkillData.Skill1Icon))
			{
				Skill1Widget->SetSkillIcon(SkillData.Skill1Icon);
			}

			if (Skill2Widget && IsValid(SkillData.Skill2Icon))
			{
				Skill2Widget->SetSkillIcon(SkillData.Skill2Icon);
			}

			if (Skill3Widget && IsValid(SkillData.Skill3Icon))
			{
				Skill3Widget->SetSkillIcon(SkillData.Skill3Icon);
			}
		}
	}
}

void USW_SkillSlotWidget::StartDashDown(const float& DownTime)
{
	if (DashWidget)
	{
		DashWidget->StartSkillTimer(DownTime);
	}
}

void USW_SkillSlotWidget::StartSkill1Down(const float& DownTime)
{
	if (Skill1Widget)
	{
		Skill1Widget->StartSkillTimer(DownTime);
	}
}

void USW_SkillSlotWidget::StartSkill2Down(const float& DownTime)
{
	if (Skill2Widget)
	{
		Skill2Widget->StartSkillTimer(DownTime);
	}
}

void USW_SkillSlotWidget::StartSkill3Down(const float& DownTime)
{
	if (Skill3Widget)
	{
		Skill3Widget->StartSkillTimer(DownTime);
	}
}
