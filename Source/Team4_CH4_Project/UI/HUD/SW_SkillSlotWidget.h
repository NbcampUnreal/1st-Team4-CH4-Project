// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../SW_HUDManager.h"
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
	UTextBlock* DashTimeText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* Skill1TimeText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* Skill2TimeText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* Skill3TimeText;

	UPROPERTY()
	ECharacterType CharacterType;
	UPROPERTY()
	FSkillDataRow SkillData;

	/*
	UPROPERTY()
	TMap<ESkillType, FTimerHandle> SkillTimerHandles;
	UPROPERTY()
	TMap<ESkillType, FTimerHandle> UpdateTimerHandles;
	*/

	UPROPERTY()
	FTimerHandle DashTimerHandle;
	UPROPERTY()
	FTimerHandle Skill1TimerHandle;
	UPROPERTY()
	FTimerHandle Skill2TimerHandle;
	UPROPERTY()
	FTimerHandle Skill3TimerHandle;
	UPROPERTY()
	FTimerHandle DashUpdateHandle;
	UPROPERTY()
	FTimerHandle Skill1UpdateHandle;
	UPROPERTY()
	FTimerHandle Skill2UpdateHandle;
	UPROPERTY()
	FTimerHandle Skill3UpdateHandle;

	UFUNCTION(BlueprintCallable)
	void SetSkillIcons(ECharacterType Type);

	UFUNCTION(BlueprintCallable)
	void StartSkill1Timer(const float& DownTime);
	UFUNCTION(BlueprintCallable)
	void UpdateSkill1Timer();
	UFUNCTION(BlueprintCallable)
	void StopSkill1Timer();
	UFUNCTION(BlueprintCallable)
	void StartSkill2Timer(const float& DownTime);
	UFUNCTION(BlueprintCallable)
	void UpdateSkill2Timer();
	UFUNCTION(BlueprintCallable)
	void StopSkill2Timer();
	UFUNCTION(BlueprintCallable)
	void StartSkill3Timer(const float& DownTime);
	UFUNCTION(BlueprintCallable)
	void UpdateSkill3Timer();
	UFUNCTION(BlueprintCallable)
	void StopSkill3Timer();
	UFUNCTION(BlueprintCallable)
	void StartDashTimer(const float& DownTime);
	UFUNCTION(BlueprintCallable)
	void UpdateDashTimer();
	UFUNCTION(BlueprintCallable)
	void StopDashTimer();

	/*
	UFUNCTION(BlueprintCallable)
	void StartSkillTimer(const ESkillType& SkillDown);

	UFUNCTION(BlueprintCallable)
	void UpdateSkillTimer(const FTimerHandle& TimerHandle, UTextBlock* Text, UImage* Icon);

	UFUNCTION(BlueprintCallable)
	void StopSkillTimer(FTimerHandle& UpdateHandle, UTextBlock* Text, UImage* Icon);
	*/
};
