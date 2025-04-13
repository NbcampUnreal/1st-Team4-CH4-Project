// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SW_SkillWidget.generated.h"

class UImage;
class UTextBlock;

UCLASS(meta=(DisableNativeTick))
class TEAM4_CH4_PROJECT_API USW_SkillWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* SkillIcon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* InputText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* DownTimeText;
	UPROPERTY(BlueprintReadOnly)
	FTimerHandle DownHandle;
	UPROPERTY(BlueprintReadOnly)
	FTimerHandle UpdateHandle;

	FLinearColor DownColor = FLinearColor(0.3f, 0.3f, 0.3f, 0.3f);

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void SetSkillIcon(UTexture2D* Icon);
	UFUNCTION(BlueprintCallable)
	void SetInputText(const FText& InText);
	UFUNCTION(BlueprintCallable)
	void StartSkillTimer(const float& DownTime);
	UFUNCTION(BlueprintCallable)
	void UpdateSkillTimer();
	UFUNCTION(BlueprintCallable)
	void StopSkillTimer();
};
