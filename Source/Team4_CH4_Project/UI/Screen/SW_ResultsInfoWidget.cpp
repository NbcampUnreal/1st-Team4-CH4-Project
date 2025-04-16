
#include "SW_ResultsInfoWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"

void USW_ResultsInfoWidget::SetResultImage(UTexture2D* ResultTexture)
{
	if (ResultImage)
	{
		ResultImage->SetBrushFromTexture(ResultTexture);
	}
}

void USW_ResultsInfoWidget::SetNameText(const FText& PlayerName)
{
	if (NameText)
	{
		NameText->SetText(PlayerName);
	}
}

void USW_ResultsInfoWidget::SetRankText(const int32& Rank)
{
	if (RankText)
	{
		RankText->SetText(FText::AsNumber(Rank));
	}

	if (Rank == 1)
	{
		RankBorder->SetBrushColor(FLinearColor(1.f, 0.3f, 0.f));
	}
	else
	{
		RankBorder->SetBrushColor(FLinearColor(0.5f, 0.5f, 0.5f));
	}
}

//void USW_ResultsInfoWidget::SetTimeText(const int32& Minutes, const int32& Seconds)
//{
//	if (TimeText)
//	{
//		TimeText->SetText(FText::FromString(FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds)));
//	}
//}

