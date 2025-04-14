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
#include "UI/HUD_SJE/SW_HUD.h"

ASW_CharacterPlayer::ASW_CharacterPlayer()
	: ASW_CharacterBase()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 1400.f;
	CameraBoom->SetRelativeRotation(FRotator(-40.f, 0.f, 0.f));
	CameraBoom->bUsePawnControlRotation = false;
	CameraBoom->bInheritYaw = false;
	CameraBoom->bInheritPitch = false;
	CameraBoom->bInheritRoll = false;
	CameraBoom->bDoCollisionTest = false;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom);
	FollowCamera->bUsePawnControlRotation = false;
}

void ASW_CharacterPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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

	AbilitySystemComponent = Cast<USW_AbilitySystemComponent>(SW_PlayerState->GetAbilitySystemComponent());
	AttributeSet = Cast<USW_AttributeSet>(SW_PlayerState->GetAttributeSet());
	
	
	if (ASW_PlayerController* SW_PlayerController = Cast<ASW_PlayerController>(GetController()))
	{
		if (ASW_HUD* SW_HUD = Cast<ASW_HUD>(SW_PlayerController->GetHUD()))
		{
			SW_HUD->InitOverlay(SW_PlayerController, SW_PlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
}
