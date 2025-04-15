// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../SW_HUDManager.h"
#include "SW_SkillSlotWidget.generated.h"

class UImage;
class UTextBlock;
class USW_SkillWidget;

UCLASS()
class TEAM4_CH4_PROJECT_API USW_SkillSlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	USW_SkillWidget* AttackWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	USW_SkillWidget* GuardWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	USW_SkillWidget* DashWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	USW_SkillWidget* Skill1Widget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	USW_SkillWidget* Skill2Widget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	USW_SkillWidget* Skill3Widget;

	UFUNCTION(BlueprintCallable)
	void SetSkillIcons(ECharacterType Type);
	UFUNCTION(BlueprintCallable)
	void PlaySkillAnim(ESkillType SkillType);
	UFUNCTION(BlueprintCallable)
	void StartDashDown(const float& DownTime);
	UFUNCTION(BlueprintCallable)
	void StartSkill1Down(const float& DownTime);
	UFUNCTION(BlueprintCallable)
	void StartSkill2Down(const float& DownTime);
	UFUNCTION(BlueprintCallable)
	void StartSkill3Down(const float& DownTime);
};
