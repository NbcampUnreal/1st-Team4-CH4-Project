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
				AttackWidget->SetSkillType(ESkillType::Attack);
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
				DashWidget->SetSkillType(ESkillType::Dash);
			}

			if (Skill1Widget && IsValid(SkillData.Skill1Icon))
			{
				Skill1Widget->SetSkillIcon(SkillData.Skill1Icon);
				Skill1Widget->SetInputText(FText::FromString(TEXT("H")));
				Skill1Widget->SetSkillType(ESkillType::Skill1);
			}

			if (Skill2Widget && IsValid(SkillData.Skill2Icon))
			{
				Skill2Widget->SetSkillIcon(SkillData.Skill2Icon);
				Skill2Widget->SetInputText(FText::FromString(TEXT("J")));
				Skill2Widget->SetSkillType(ESkillType::Skill2);
			}
			
			if (Skill3Widget && IsValid(SkillData.Skill3Icon))
			{
				Skill3Widget->SetSkillIcon(SkillData.Skill3Icon);
				Skill3Widget->SetInputText(FText::FromString(TEXT("SPACE+K")));
				Skill3Widget->SetSkillType(ESkillType::Skill3);
			}
		}
	}
}

void USW_SkillSlotWidget::PlaySkillAnim(ESkillType SkillType)
{
	switch (SkillType)
	{
	case ESkillType::Attack:
		if (AttackWidget)
		{
			AttackWidget->PlaySkillAnim();
		}
		break;
	case ESkillType::Dash:
		if (DashWidget)
		{
			DashWidget->PlaySkillAnim();
		}
		break;
	case ESkillType::Skill1:
		if (Skill1Widget)
		{
			Skill1Widget->PlaySkillAnim();
		}
		break;
	case ESkillType::Skill2:
		if (Skill2Widget)
		{
			Skill2Widget->PlaySkillAnim();
		}
		break;
	case ESkillType::Skill3:
		if (Skill3Widget)
		{
			Skill3Widget->PlaySkillAnim();
		}
		break;
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
