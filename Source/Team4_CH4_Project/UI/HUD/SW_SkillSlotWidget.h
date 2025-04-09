// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../CharacterData/SW_CharacterType.h"
#include "SW_SkillSlotWidget.generated.h"

class UImage;
class UTextBlock;

UCLASS()
class TEAM4_CH4_PROJECT_API USW_SkillSlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* AttackIcon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* GuardIcon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* DashIcon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* Skill1Icon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* Skill2Icon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* Skill3Icon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* Skill1TimeText;

	UPROPERTY()
	TArray<FTimerHandle> SkillTimerHandles;
	UPROPERTY()
	TArray<FTimerHandle> UpdateTimerHandles;

	UPROPERTY()
	FTimerHandle Skill1TimerHandle;
	UPROPERTY()
	FTimerHandle Skill1UpdateHandle;

	UFUNCTION(BlueprintCallable)
	void SetSkillIcons(ECharacterType CharacterType);

	UFUNCTION(BlueprintCallable)
	void StartSkill1Timer(const float& RemainingTime);

	UFUNCTION(BlueprintCallable)
	void UpdateSkill1TimeText();

	UFUNCTION(BlueprintCallable)
	void StopSkill1Timer();
};
