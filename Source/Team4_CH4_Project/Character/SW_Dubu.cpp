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

}

void ASW_Dubu::Player_Move(const FInputActionValue& _InputValue)
{
	const FVector2D MoveVector = _InputValue.Get<FVector2D>();
	if (MoveVector.IsNearlyZero())
	{
		return;
	}

	FRotator ControlRotation = GetControlRotation();
	FRotator YawRotation(0, ControlRotation.Yaw, 0);
	FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(ForwardDirection, MoveVector.Y);
	AddMovementInput(RightDirection, MoveVector.X);
}

void ASW_Dubu::Player_Jump(const FInputActionValue& _InputValue)
{
	bool bJump = _InputValue.Get<bool>();
	if (bJump)
	{
		Jump();
	}
}
