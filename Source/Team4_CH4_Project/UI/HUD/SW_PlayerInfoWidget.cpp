// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_PlayerInfoWidget.h"
#include "../SW_HUDManager.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/HorizontalBox.h"

void USW_PlayerInfoWidget::SetThumbnailByType(ECharacterType Type)
{
	if (UGameInstance* GameInstance = GetGameInstance())
	{
		if (USW_HUDManager* HUDManager = GameInstance->GetSubsystem<USW_HUDManager>())
		{
			FCharacterDataRow CharacterData = HUDManager->GetCharacterData(Type);
			if (PlayerThumbnail && IsValid(CharacterData.CharacterImage))
			{
				PlayerThumbnail->SetBrushFromTexture(CharacterData.CharacterImage);
			}
		}
	}
}

void USW_PlayerInfoWidget::UpdateLifeIcons(int32 LifeNum)
{
	if (RemainingLives == LifeNum)
	{
		return;
	}

	RemainingLives = LifeNum;

	TArray<UWidget*> Children = LifeHBox->GetAllChildren();
	if (Children.IsValidIndex(LifeNum - 1))
	{
		for (int32 i = 0; i < LifeNum; i++)
		{
			Children[i]->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		}
		for (int32 i = LifeNum; i < Children.Num(); i++)
		{
			Children[i]->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

