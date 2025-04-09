// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_SkillSlotWidget.h"
#include "../SW_HUDManager.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void USW_SkillSlotWidget::SetSkillIcons(ECharacterType CharacterType)
{
	if (UGameInstance* GameInstance = GetGameInstance())
	{
		if (USW_HUDManager* HUDManager = GameInstance->GetSubsystem<USW_HUDManager>())
		{
			FSkillDataRow SkillData = HUDManager->GetSkillData(CharacterType);

			if (AttackIcon && IsValid(SkillData.AttackIcon))
			{
				AttackIcon->SetBrushFromTexture(SkillData.AttackIcon);
			}

			if (GuardIcon && IsValid(SkillData.GuardIcon))
			{
				GuardIcon->SetBrushFromTexture(SkillData.GuardIcon);
			}

			if (DashIcon && IsValid(SkillData.DashIcon))
			{
				DashIcon->SetBrushFromTexture(SkillData.DashIcon);
			}

			if (Skill1Icon && IsValid(SkillData.Skill1Icon))
			{
				Skill1Icon->SetBrushFromTexture(SkillData.Skill1Icon);
			}

			if (Skill2Icon && IsValid(SkillData.Skill2Icon))
			{
				Skill2Icon->SetBrushFromTexture(SkillData.Skill2Icon);
			}

			if (Skill3Icon && IsValid(SkillData.Skill3Icon))
			{
				Skill3Icon->SetBrushFromTexture(SkillData.Skill3Icon);
			}
		}
	}
}

void USW_SkillSlotWidget::StartSkill1Timer(const float& RemainingTime)
{
	if (RemainingTime <= 0)
	{
		return;
	}

	if (Skill1TimeText && Skill1Icon)
	{
		Skill1TimeText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		Skill1Icon->SetColorAndOpacity(FLinearColor(0.f, 0.f, 0.f, 0.5f));
	}

	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(
			Skill1UpdateHandle,
			this,
			&USW_SkillSlotWidget::UpdateSkill1TimeText,
			0.1f,
			true
		);
	}
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(
			Skill1TimerHandle,
			this,
			&USW_SkillSlotWidget::StopSkill1Timer,
			RemainingTime,
			false
		);
	}
}

void USW_SkillSlotWidget::UpdateSkill1TimeText()
{
	if (Skill1TimeText && GetWorld())
	{
		float RemainingTime = GetWorld()->GetTimerManager().GetTimerRemaining(Skill1TimerHandle);
		FText RemainingTimeText = FText::FromString(FString::Printf(TEXT("%.0f"), RemainingTime));
		Skill1TimeText->SetText(RemainingTimeText);
	}
}

void USW_SkillSlotWidget::StopSkill1Timer()
{
	if (Skill1TimeText && Skill1Icon)
	{
		Skill1TimeText->SetVisibility(ESlateVisibility::Collapsed);
		Skill1Icon->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 1.f));
	}
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(Skill1TimerHandle);
		GetWorld()->GetTimerManager().ClearTimer(Skill1UpdateHandle);
	}
}


