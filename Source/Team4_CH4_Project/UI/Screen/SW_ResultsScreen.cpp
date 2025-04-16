// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_ResultsScreen.h"
#include "SW_ResultsInfoWidget.h"
#include "Animation/WidgetAnimation.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void USW_ResultsScreen::NativeConstruct()
{
	Super::NativeConstruct();

	if (EnterAnim)
	{
		EnterAnimFinished.BindDynamic(this, &USW_ResultsScreen::DisplayButtons);
		BindToAnimationFinished(EnterAnim, EnterAnimFinished);
		PlayAnimation(EnterAnim);
	}

	if (ReturnButton)
	{
		ReturnButton->OnClicked.AddDynamic(this, &USW_ResultsScreen::ExitScreen);
	}
}

void USW_ResultsScreen::SetResultImage(const bool& bHasWon)
{
	if (bHasWon && ResultImage && BigWinTexture)
	{
		ResultImage->SetBrushFromTexture(BigWinTexture);
	}
}

void USW_ResultsScreen::SetTimeText(const FText& InTimeText)
{
	if (TimeText)
	{
		TimeText->SetText(InTimeText);
	}
}

// TODO: change parameter to struct
void USW_ResultsScreen::AddPlayerInfo(const FSW_ResultData& ResultData)
{
	if (PlayerInfoBox && PlayerInfoWidgetClass && !ResultData.PlayerName.IsEmpty())
	{
		USW_ResultsInfoWidget* PlayerInfoWidget = CreateWidget<USW_ResultsInfoWidget>(this, PlayerInfoWidgetClass);
		if (PlayerInfoWidget)
		{
			PlayerInfoWidget->SetNameText(FText::FromString(ResultData.PlayerName));
			PlayerInfoWidget->SetRankText(ResultData.Rank);
			if (ResultData.bHasWon)
			{
				PlayerInfoWidget->SetResultImage(SmallWinTexture);
			}
			PlayerInfoBox->AddChildToVerticalBox(PlayerInfoWidget);
			if (UVerticalBoxSlot* PlayerInfoSlot = Cast<UVerticalBoxSlot>(PlayerInfoWidget->Slot))
			{
				PlayerInfoSlot->SetPadding(FMargin(0.f, 0.f, 0.f, 15.f));
			}
			PlayerInfoWidget->AddToViewport();
		}
	}
}

void USW_ResultsScreen::ExitScreen()
{
	if (ExitAnim)
	{
		PlayAnimation(ExitAnim);
	}
}

void USW_ResultsScreen::DisplayButtons()
{
	if (ReturnButton)
	{
		ReturnButton->SetVisibility(ESlateVisibility::Visible);
	}
}

void USW_ResultsScreen::RemoveScreen()
{
	if (GetWorld() && GetWorld()->bIsTearingDown && IsValidLowLevel())
	{
		if (PlayerInfoBox)
		{
			PlayerInfoBox->ClearChildren();
			RemoveFromParent();
		}
	}
}

