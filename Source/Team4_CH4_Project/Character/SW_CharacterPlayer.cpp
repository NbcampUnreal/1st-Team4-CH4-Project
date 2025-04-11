// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_CharacterPlayer.h"
#include "SW_PlayerController.h"
#include "Kismet/GamePlayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/SW_PlayerState.h"
#include "AbilitySystem/SW_AbilitySystemComponent.h"
#include "AbilitySystem/SW_AttributeSet.h"

ASW_CharacterPlayer::ASW_CharacterPlayer()
	: ASW_CharacterBase()
{
	SpringBoomLength = 300.f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = SpringBoomLength;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	FollowCamera->SetupAttachment(CameraBoom);
	FollowCamera->bUsePawnControlRotation = false;

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);
}

void ASW_CharacterPlayer::BeginPlay()
{
	Super::BeginPlay();
}

void ASW_CharacterPlayer::Player_Move(const FInputActionValue& _InputValue)
{
	const FVector2D MoveVector = _InputValue.Get<FVector2D>();
	if (MoveVector.IsNearlyZero())
	{
		return;
	}
	FRotator ControlRotation = GetControlRotation();
	FRotator YawRotation(0, ControlRotation.Yaw, 0);
	FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(ForwardDirection, MoveVector.Y);
	AddMovementInput(RightDirection, MoveVector.X);
}

void ASW_CharacterPlayer::Player_Jump(const FInputActionValue& _InputValue)
{
	bool bJump = _InputValue.Get<bool>();
	if(bJump)
	{
		Jump();
	}
}

void ASW_CharacterPlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init ability actor info for server
	InitAbilityActorInfo();
}

void ASW_CharacterPlayer::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Init ability actor info for client
	InitAbilityActorInfo();
}

void ASW_CharacterPlayer::InitAbilityActorInfo()
{
	ASW_PlayerState* SW_PlayerState = GetPlayerState<ASW_PlayerState>();
	check(SW_PlayerState);
	SW_PlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(SW_PlayerState, this);
	AbilitySystemComponent = SW_PlayerState->GetAbilitySystemComponent();
	AttributeSet = SW_PlayerState->GetAttributeSet();
}
