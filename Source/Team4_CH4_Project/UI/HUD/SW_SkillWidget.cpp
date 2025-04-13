// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_SkillWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void USW_SkillWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void USW_SkillWidget::SetSkillIcon(UTexture2D* Icon)
{
	if (SkillIcon && IsValid(Icon))
	{
		SkillIcon->SetBrushFromTexture(Icon);
	}
}

void USW_SkillWidget::SetInputText(const FText& InText)
{
	if (InputText && !InText.IsEmpty())
	{
		InputText->SetText(InText);
	}
}

void USW_SkillWidget::StartSkillTimer(const float& DownTime)
{
	if (DownTimeText && SkillIcon)
	{
		DownTimeText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		// UITODO : 쿨타임 시 머티리얼 적용?
		SkillIcon->SetColorAndOpacity(DownColor);
	}

	if (GetWorld())
	{
		// Repeatedly update down time
		GetWorld()->GetTimerManager().SetTimer(
			UpdateHandle,
			this,
			&USW_SkillWidget::UpdateSkillTimer,
			0.1f,
			true
		);

		// Stop updating and displaying down time
		GetWorld()->GetTimerManager().SetTimer(
			DownHandle,
			this,
			&USW_SkillWidget::StopSkillTimer,
			DownTime,
			true
		);
	}
}

void USW_SkillWidget::UpdateSkillTimer()
{
	// Display remaining time on the skill timer
	if (DownTimeText && GetWorld())
	{
		float RemainingTime = GetWorld()->GetTimerManager().GetTimerRemaining(DownHandle);
		FText RemainingTimeText = FText::FromString(
			RemainingTime < 1.f ?
			FString::Printf(TEXT("%.1f"), RemainingTime) :
			FString::Printf(TEXT("%d"), FMath::TruncToInt32(RemainingTime)));
		DownTimeText->SetText(RemainingTimeText);
	}
}

void USW_SkillWidget::StopSkillTimer()
{
	// Stop updating down time
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(UpdateHandle);
	}

	// Hide down time indicator
	if (DownTimeText && SkillIcon)
	{
		DownTimeText->SetVisibility(ESlateVisibility::Collapsed);
		SkillIcon->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 1.f));
	}
}
