#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../GameData/SW_ResultData.h"
#include "SW_ResultsScreen.generated.h"

class UButton;
class UVerticalBox;
class UImage;
class UTextBlock;

UCLASS()
class TEAM4_CH4_PROJECT_API USW_ResultsScreen : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* EnterAnim;
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* ExitAnim;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UImage* ResultImage;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* TimeText;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UButton* ReturnButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UVerticalBox* PlayerInfoBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Assets")
	UTexture2D* BigWinTexture;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Assets")
	UTexture2D* SmallWinTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChildWidgets")
	TSubclassOf<UUserWidget> PlayerInfoWidgetClass;

	FWidgetAnimationDynamicEvent EnterAnimFinished;
	FWidgetAnimationDynamicEvent ExitAnimFinished;

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void EnterScreen();
	UFUNCTION(BlueprintCallable)
	void ExitScreen();

	UFUNCTION(BlueprintCallable)
	void SetResultImage(const bool& bHasWon);
	UFUNCTION(BlueprintCallable)
	void SetTimeText(const FText& InTimeText);
	UFUNCTION(BlueprintCallable)
	void AddPlayerInfo(const FSW_ResultData& ResultData);

private:
	UFUNCTION(BlueprintCallable)
	void DisplayButtons();

	UFUNCTION(BlueprintCallable)
	void RemoveScreen();
};
