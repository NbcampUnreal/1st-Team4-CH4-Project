// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_PlayerController.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "SW_CharacterPlayer.h"

ASW_PlayerController::ASW_PlayerController()
	: InputMappingContext(nullptr)
	, MoveAction(nullptr)
	, JumpAction(nullptr)
	, AttackBasicAction(nullptr)
{
}

void ASW_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Add Mapping Input Context
	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (InputMappingContext)
			{
				Subsystem->AddMappingContext(InputMappingContext, 0);
			}
		}
	}
}

void ASW_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
	{
		if (MoveAction)
		{
			EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASW_PlayerController::PlayerMove);
		}
	}
}

void ASW_PlayerController::PlayerMove(const FInputActionValue& _InputValue)
{
	ASW_CharacterPlayer* PlayerCharacter = Cast<ASW_CharacterPlayer>(GetPawn());
	if (PlayerCharacter)
	{
		PlayerCharacter->Player_Move(_InputValue);
	}
}


