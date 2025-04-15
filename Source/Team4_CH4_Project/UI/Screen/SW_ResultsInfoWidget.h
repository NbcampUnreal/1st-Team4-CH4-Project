#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SW_ResultsInfoWidget.generated.h"

class UTextBlock;
class UImage;
class UBorder;

UCLASS()
class TEAM4_CH4_PROJECT_API USW_ResultsInfoWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UImage* ResultImage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* RankText;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* NameText;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UBorder* RankBorder;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	//UTextBlock* TimeText;

	UFUNCTION(BlueprintCallable)
	void SetResultImage(UTexture2D* ResultTexture);

	UFUNCTION(BlueprintCallable)
	void SetNameText(const FText& PlayerName);

	UFUNCTION(BlueprintCallable)
	void SetRankText(const int32& Rank);

	//UFUNCTION(BlueprintCallable)
	//void SetTimeText(const int32& Minutes, const int32& Seconds);
};
