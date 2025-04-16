#include "SW_PlayerController.h"
#include "SW_CharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "UI/SW_HUDManager.h"
#include "UI/ViewModels/SW_SkillViewModel.h"

ASW_PlayerController::ASW_PlayerController()
    : InputMappingContext(nullptr)
    , MoveAction(nullptr)
    , JumpAction(nullptr)
    , ComboAttackAction(nullptr)
    , DashSkillAction(nullptr)
    , NormalSkillAction(nullptr)
    , SpecialSkillAction(nullptr)
    , JumpAttackAction(nullptr)
{
}

void ASW_PlayerController::BeginPlay()
{
    Super::BeginPlay();

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

void ASW_PlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
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
        if (JumpAction)
        {
            EnhancedInput->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ASW_PlayerController::PlayerJump);
        }
        if (ComboAttackAction)
        {
            EnhancedInput->BindAction(ComboAttackAction, ETriggerEvent::Started, this, &ASW_PlayerController::ComboAttack);
        }
        if (JumpAttackAction)
        {
            EnhancedInput->BindAction(JumpAttackAction, ETriggerEvent::Started, this, &ASW_PlayerController::JumpAttack);
        }
        if (NormalSkillAction)
        {
            EnhancedInput->BindAction(NormalSkillAction, ETriggerEvent::Started, this, &ASW_PlayerController::NormalSkill);
        }
        if (SpecialSkillAction)
        {
            EnhancedInput->BindAction(SpecialSkillAction, ETriggerEvent::Started, this, &ASW_PlayerController::SpecialSkill);
        }
        if (DashSkillAction)
        {
            EnhancedInput->BindAction(DashSkillAction, ETriggerEvent::Started, this, &ASW_PlayerController::DashSkill);
        }
    }
}

void ASW_PlayerController::PlayerMove(const FInputActionValue& _InputValue)
{
    if (ASW_CharacterBase* PlayerCharacter = Cast<ASW_CharacterBase>(GetPawn()))
    {
        if (!PlayerCharacter->bIsLocked)
        {
            PlayerCharacter->Player_Move(_InputValue);
        }
    }
}

void ASW_PlayerController::PlayerJump(const FInputActionValue& _InputValue)
{
    if (ASW_CharacterBase* PlayerCharacter = Cast<ASW_CharacterBase>(GetPawn()))
    {
        if (!PlayerCharacter->bIsLocked)
        {
            PlayerCharacter->Player_Jump(_InputValue);
        }
    }
}

void ASW_PlayerController::ComboAttack(const FInputActionValue& InputValue)
{
    if (ASW_CharacterBase* PlayerCharacter = Cast<ASW_CharacterBase>(GetPawn()))
    {
        if (PlayerCharacter->GetCharacterMovement()->IsFalling())
        {
            return;
        }

        // 애니메이션 재생중엔 잠금이 걸리지만, ComboInput 노티파이가 활성화된 상태면 입력 저장 허용
        if (PlayerCharacter->bIsLocked)
        {
            if (PlayerCharacter->bComboInputActive)
            {
                PlayerCharacter->bComboQueued = true;
            }
        }
        else
        {
            PlayerCharacter->Server_PlaySkill("ComboAttack");
        }
    }
}

void ASW_PlayerController::JumpAttack(const FInputActionValue& InputValue)
{
    if (ASW_CharacterBase* PlayerCharacter = Cast<ASW_CharacterBase>(GetPawn()))
    {
        // 점프 중이면서 점프어택 중이 아닐 때만 입력 가능
        if (!PlayerCharacter->bIsLocked &&
            PlayerCharacter->GetCharacterMovement()->IsFalling() &&
            !PlayerCharacter->bIsJumpAttacking)
        {
            PlayerCharacter->Server_PlaySkill("JumpAttack");
        }
    }
}


void ASW_PlayerController::NormalSkill(const FInputActionValue& InputValue)
{
    if (ASW_CharacterBase* PlayerCharacter = Cast<ASW_CharacterBase>(GetPawn()))
    {
        if (!PlayerCharacter->bIsLocked && !PlayerCharacter->GetCharacterMovement()->IsFalling())
        {
            PlayerCharacter->Server_PlaySkill("NormalSkill");
        }
    }
}

void ASW_PlayerController::SpecialSkill(const FInputActionValue& InputValue)
{
    if (ASW_CharacterBase* PlayerCharacter = Cast<ASW_CharacterBase>(GetPawn()))
    {
        if (!PlayerCharacter->bIsLocked && !PlayerCharacter->GetCharacterMovement()->IsFalling())
        {
            PlayerCharacter->Server_PlaySkill("SpecialSkill");
        }
    }
}

void ASW_PlayerController::DashSkill(const FInputActionValue& InputValue)
{
    if (ASW_CharacterBase* PlayerCharacter = Cast<ASW_CharacterBase>(GetPawn()))
    {
        if (!PlayerCharacter->bIsLocked && !PlayerCharacter->GetCharacterMovement()->IsFalling())
        {
            PlayerCharacter->Server_PlaySkill("DashSkill");
        }
    }
}