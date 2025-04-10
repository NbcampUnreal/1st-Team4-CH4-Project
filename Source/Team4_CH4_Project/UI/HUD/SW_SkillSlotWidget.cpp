// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_SkillSlotWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

/*
void USW_SkillSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	for (uint8 i = 0; i < static_cast<uint8>(ESkillType::MAX); ++i)
	{
		SkillTimerHandles.Add(static_cast<ESkillType>(i), FTimerHandle());
		UpdateTimerHandles.Add(static_cast<ESkillType>(i), FTimerHandle());
	}
}
*/

void USW_SkillSlotWidget::SetSkillIcons(ECharacterType Type)
{
	CharacterType = Type;

	if (UGameInstance* GameInstance = GetGameInstance())
	{
		if (USW_HUDManager* HUDManager = GameInstance->GetSubsystem<USW_HUDManager>())
		{
			SkillData = HUDManager->GetSkillData(CharacterType);

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

void USW_SkillSlotWidget::StartSkill1Timer(const float& DownTime)
{
	if (Skill1TimeText && Skill1Icon)
	{
		Skill1TimeText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		Skill1Icon->SetColorAndOpacity(FLinearColor(0.f, 0.f, 0.f, 0.5f));
	}

	if (GetWorld())
	{
		// Repeatedly update down time
		GetWorld()->GetTimerManager().SetTimer(
			Skill1UpdateHandle,
			this,
			&USW_SkillSlotWidget::UpdateSkill1Timer,
			0.1f,
			true
		);

		// Stop updating and displaying down time
		GetWorld()->GetTimerManager().SetTimer(
			Skill1TimerHandle,
			this,
			&USW_SkillSlotWidget::StopSkill1Timer,
			DownTime,
			true
		);
	}
}

void USW_SkillSlotWidget::UpdateSkill1Timer()
{
	// Display remaining time on the skill timer
	if (Skill1TimeText && GetWorld())
	{
		float RemainingTime = GetWorld()->GetTimerManager().GetTimerRemaining(Skill1TimerHandle);
		FText RemainingTimeText = FText::FromString(
			RemainingTime < 1.f ?
			FString::Printf(TEXT("%.1f"), RemainingTime) :
			FString::Printf(TEXT("%d"), FMath::TruncToInt32(RemainingTime)));
		Skill1TimeText->SetText(RemainingTimeText);
	}
}

void USW_SkillSlotWidget::StopSkill1Timer()
{
	// Stop updating down time
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(Skill1UpdateHandle);
	}

	// Hide down time indicator
	if (Skill1TimeText && Skill1Icon)
	{
		Skill1TimeText->SetVisibility(ESlateVisibility::Collapsed);
		Skill1Icon->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 1.f));
	}
}

void USW_SkillSlotWidget::StartSkill2Timer(const float& DownTime)
{
	if (Skill2TimeText && Skill2Icon)
	{
		Skill2TimeText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		Skill2Icon->SetColorAndOpacity(FLinearColor(0.f, 0.f, 0.f, 0.5f));
	}

	if (GetWorld())
	{
		// Repeatedly update down time
		GetWorld()->GetTimerManager().SetTimer(
			Skill2UpdateHandle,
			this,
			&USW_SkillSlotWidget::UpdateSkill2Timer,
			0.1f,
			true
		);

		// Stop updating and displaying down time
		GetWorld()->GetTimerManager().SetTimer(
			Skill2TimerHandle,
			this,
			&USW_SkillSlotWidget::StopSkill2Timer,
			DownTime,
			true
		);
	}
}

void USW_SkillSlotWidget::UpdateSkill2Timer()
{
	// Display remaining time on the skill timer
	if (Skill2TimeText && GetWorld())
	{
		float RemainingTime = GetWorld()->GetTimerManager().GetTimerRemaining(Skill2TimerHandle);
		FText RemainingTimeText = FText::FromString(
			RemainingTime < 1.f ?
			FString::Printf(TEXT("%.1f"), RemainingTime) :
			FString::Printf(TEXT("%d"), FMath::TruncToInt32(RemainingTime)));
		Skill2TimeText->SetText(RemainingTimeText);
	}
}

void USW_SkillSlotWidget::StopSkill2Timer()
{
	// Stop updating down time
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(Skill2UpdateHandle);
	}

	// Hide down time indicator
	if (Skill2TimeText && Skill2Icon)
	{
		Skill2TimeText->SetVisibility(ESlateVisibility::Collapsed);
		Skill2Icon->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 1.f));
	}
}

void USW_SkillSlotWidget::StartSkill3Timer(const float& DownTime)
{
	if (Skill3TimeText && Skill3Icon)
	{
		Skill3TimeText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		Skill3Icon->SetColorAndOpacity(FLinearColor(0.f, 0.f, 0.f, 0.5f));
	}

	if (GetWorld())
	{
		// Repeatedly update down time
		GetWorld()->GetTimerManager().SetTimer(
			Skill3UpdateHandle,
			this,
			&USW_SkillSlotWidget::UpdateSkill3Timer,
			0.1f,
			true
		);

		// Stop updating and displaying down time
		GetWorld()->GetTimerManager().SetTimer(
			Skill3TimerHandle,
			this,
			&USW_SkillSlotWidget::StopSkill3Timer,
			DownTime,
			true
		);
	}
}

void USW_SkillSlotWidget::UpdateSkill3Timer()
{
	// Display remaining time on the skill timer
	if (Skill3TimeText && GetWorld())
	{
		float RemainingTime = GetWorld()->GetTimerManager().GetTimerRemaining(Skill3TimerHandle);
		FText RemainingTimeText = FText::FromString(
			RemainingTime < 1.f ?
			FString::Printf(TEXT("%.1f"), RemainingTime) :
			FString::Printf(TEXT("%d"), FMath::TruncToInt32(RemainingTime)));
		Skill3TimeText->SetText(RemainingTimeText);
	}
}

void USW_SkillSlotWidget::StopSkill3Timer()
{
	// Stop updating down time
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(Skill3UpdateHandle);
	}

	// Hide down time indicator
	if (Skill3TimeText && Skill3Icon)
	{
		Skill3TimeText->SetVisibility(ESlateVisibility::Collapsed);
		Skill3Icon->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 1.f));
	}
}

void USW_SkillSlotWidget::StartDashTimer(const float& DownTime)
{
	if (DashTimeText && DashIcon)
	{
		DashTimeText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		DashIcon->SetColorAndOpacity(FLinearColor(0.f, 0.f, 0.f, 0.5f));
	}

	if (GetWorld())
	{
		// Repeatedly update down time
		GetWorld()->GetTimerManager().SetTimer(
			DashUpdateHandle,
			this,
			&USW_SkillSlotWidget::UpdateDashTimer,
			0.1f,
			true
		);

		// Stop updating and displaying down time
		GetWorld()->GetTimerManager().SetTimer(
			DashTimerHandle,
			this,
			&USW_SkillSlotWidget::StopDashTimer,
			DownTime,
			true
		);
	}
}

void USW_SkillSlotWidget::UpdateDashTimer()
{
	// Display remaining time on the skill timer
	if (DashTimeText && GetWorld())
	{
		float RemainingTime = GetWorld()->GetTimerManager().GetTimerRemaining(DashTimerHandle);
		FText RemainingTimeText = FText::FromString(
			RemainingTime < 1.f ?
			FString::Printf(TEXT("%.1f"), RemainingTime) :
			FString::Printf(TEXT("%d"), FMath::TruncToInt32(RemainingTime)));
		DashTimeText->SetText(RemainingTimeText);
	}
}

void USW_SkillSlotWidget::StopDashTimer()
{
	// Stop updating down time
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(DashUpdateHandle);
	}

	// Hide down time indicator
	if (DashTimeText && DashIcon)
	{
		DashTimeText->SetVisibility(ESlateVisibility::Collapsed);
		DashIcon->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 1.f));
	}
}



/*
void USW_SkillSlotWidget::StartSkillTimer(const ESkillType& SkillDown)
{	
	UTextBlock* SkillTimeText;
	UImage* SkillIcon;
	float SkillDownTime = -1.f;
	switch (SkillDown)
	{
	case ESkillType::Dash:
		SkillDownTime = SkillData.DashTime;
		SkillTimeText = DashTimeText;
		SkillIcon = DashIcon;
		break;
	case ESkillType::Skill1:
		SkillDownTime = SkillData.Skill1Time;
		SkillTimeText = Skill1TimeText;
		SkillIcon = Skill1Icon;
		break;
	case ESkillType::Skill2:
		SkillDownTime = SkillData.Skill2Time;
		SkillTimeText = Skill2TimeText;
		SkillIcon = Skill2Icon;
		break;
	case ESkillType::Skill3:
		SkillDownTime = SkillData.Skill3Time;
		SkillTimeText = Skill3TimeText;
		SkillIcon = Skill3Icon;
		break;
	default:
		// Down time is not applicable to the other skill types
		return;
	}

	// Timer handle is not found for the specified skill type
	if (!SkillTimerHandles.Contains(SkillDown) || !UpdateTimerHandles.Contains(SkillDown))
	{
		UE_LOG(LogTemp, Warning, TEXT("!![UI]!! SkillSlotWidget - SkillTimer not found"))
			return;
	}

	// Make down time indicator visible
	if (SkillTimeText && SkillIcon)
	{
		SkillTimeText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		SkillIcon->SetColorAndOpacity(FLinearColor(0.f, 0.f, 0.f, 0.5f));
	}
	
	// Timer handles and delegates
	FTimerHandle* SkillTimerHandle = SkillTimerHandles.Find(SkillDown);
	FTimerHandle* UpdateTimerHandle = UpdateTimerHandles.Find(SkillDown);
	FTimerDelegate SkillTimerDelegate;
	SkillTimerDelegate.BindUFunction(this, "StopSkillTimer", *UpdateTimerHandle, SkillTimeText, SkillIcon);
	FTimerDelegate UpdateDelegate;
	UpdateDelegate.BindUFunction(this, "UpdateSkillTimer", *SkillTimerHandle, SkillTimeText, SkillIcon);
	if (GetWorld())
	{
		// Repeatedly update down time
		GetWorld()->GetTimerManager().SetTimer(
			*UpdateTimerHandle,
			UpdateDelegate,
			0.1f,
			true
		);

		// Stop updating and displaying down time
		GetWorld()->GetTimerManager().SetTimer(
			*SkillTimerHandle,
			SkillTimerDelegate,
			SkillDownTime,
			false
		);
	}
}

void USW_SkillSlotWidget::UpdateSkillTimer(const FTimerHandle& TimerHandle, UTextBlock* Text, UImage* Icon)
{
	// Display remaining time on the skill timer
	if (Text && GetWorld())
	{
		float RemainingTime = GetWorld()->GetTimerManager().GetTimerRemaining(TimerHandle);
		FText RemainingTimeText = FText::FromString(
			RemainingTime < 1.f ?
			FString::Printf(TEXT("%.1f"), RemainingTime) :
			FString::Printf(TEXT("%d"), FMath::TruncToInt32(RemainingTime)));
		Text->SetText(RemainingTimeText);
	}
}
void USW_SkillSlotWidget::StopSkill1Timer()
{
	// Stop updating down time
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(UpdateHandle);
	}

	// Hide down time indicator
	if (Text && Icon)
	{
		Text->SetVisibility(ESlateVisibility::Collapsed);
		Icon->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 1.f));
	}
}

*/

