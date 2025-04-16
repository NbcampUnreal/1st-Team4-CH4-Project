// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_MainHUDWidget.h"
#include "SW_MinimapWidget.h"

// UITODO : 뷰바인딩 체크?

void USW_MainHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (EnterAnim)
	{
		EnterAnimFinished.BindDynamic(this, &USW_MainHUDWidget::DisplayWidgets);
		BindToAnimationFinished(EnterAnim, EnterAnimFinished);
		PlayAnimation(EnterAnim);
	}
}

void USW_MainHUDWidget::DisplayWidgets()
{
	PlayerInfoWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	SkillSlotWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	TimeWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	MinimapWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	StartUpdateTimer();
}

void USW_MainHUDWidget::StartUpdateTimer()
{
	if (GetWorld() && !GetWorld()->bIsTearingDown)
	{
		GetWorld()->GetTimerManager().SetTimer(
			UpdateHandle,
			this,
			&USW_MainHUDWidget::UpdateMinimap,
			0.1f,
			true
		);
	}
}

void USW_MainHUDWidget::UpdateMinimap()
{
	if (IsValid(MinimapWidget) && GetVisibility() != ESlateVisibility::Collapsed)
	{
		MinimapWidget->UpdateMinimap();
	}
}

