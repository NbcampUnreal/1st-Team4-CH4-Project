#include "SW_Dubu.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"

void ASW_Dubu::BeginPlay()
{
	Super::BeginPlay();
}

ASW_Dubu::ASW_Dubu()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Combo1(TEXT("/Game/Characters/Dubu/Animation/ComboAttack/AM_Dubu_Combo_1.AM_Dubu_Combo_1"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Combo2(TEXT("/Game/Characters/Dubu/Animation/ComboAttack/AM_Dubu_Combo_2.AM_Dubu_Combo_2"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Combo3(TEXT("/Game/Characters/Dubu/Animation/ComboAttack/AM_Dubu_Combo_3.AM_Dubu_Combo_3"));

	if (Combo1.Succeeded()) ComboMontages.Add(Combo1.Object);
	if (Combo2.Succeeded()) ComboMontages.Add(Combo2.Object);
	if (Combo3.Succeeded()) ComboMontages.Add(Combo3.Object);
}

void ASW_Dubu::DashSkill()
{
	Super::DashSkill();

	FVector DashDirection = GetActorForwardVector().GetSafeNormal();
	float DashSpeed = 2500.f;

	UCharacterMovementComponent* MoveComp = GetCharacterMovement();
	MoveComp->BrakingFrictionFactor = 0.f;
	MoveComp->BrakingDecelerationWalking = 0.f;

	LaunchCharacter(DashDirection * DashSpeed, true, true);

	FTimerHandle DashResetHandle;
	GetWorldTimerManager().SetTimer(DashResetHandle, FTimerDelegate::CreateLambda([this, MoveComp]()
		{
			if (IsValid(this))
			{
				MoveComp->BrakingFrictionFactor = 2.f;
				MoveComp->BrakingDecelerationWalking = 2048.f;
			}
		}), 0.5f, false);
}
