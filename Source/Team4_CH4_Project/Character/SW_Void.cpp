// Fill out your copyright notice in the Description page of Project Settings.

#include "SW_Void.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"

ASW_Void::ASW_Void()
{
	
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Combo1(TEXT("/Game/Characters/JSH/Void/NewFolder/AM_Void_Combo1.AM_Void_Combo1"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Combo2(TEXT("/Game/Characters/JSH/Void/NewFolder/AM_Void_Combo2.AM_Void_Combo2"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Combo3(TEXT("/Game/Characters/JSH/Void/NewFolder/AM_Void_Combo3.AM_Void_Combo3"));

	if (Combo1.Succeeded()) ComboMontages.Add(Combo1.Object);
	if (Combo2.Succeeded()) ComboMontages.Add(Combo2.Object);
	if (Combo3.Succeeded()) ComboMontages.Add(Combo3.Object);
	
	MaxHealth = 80;
	Health = MaxHealth;

	// 대쉬 스킬
	FSkillData DashSkillData;
	DashSkillData.Damage = 30.f;
	DashSkillData.AttackType = ESkillAttackType::MeleeSphere;
	DashSkillData.Range = FVector(300.f); // 대시 범위: 반경 300
	DashSkillData.Offset = FVector(250.f, 0.f, 0.f); // 캐릭터 앞쪽
	SkillDataMap.Add(FName("DashSkill"), DashSkillData);
}

void ASW_Void::BeginPlay()
{
	Super::BeginPlay();
}


