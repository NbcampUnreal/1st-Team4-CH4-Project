#include "SW_PlayerController.h"
#include "SW_CharacterBase.h"
#include "Kismet/KismetMathLibrary.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

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

    bShowMouseCursor = true;
    bEnableClickEvents = true;
    bEnableMouseOverEvents = true;

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
    LookMouseCursor();
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

void ASW_PlayerController::LookMouseCursor()
{
    FHitResult Hit;
    GetHitResultUnderCursor(ECC_Visibility, false, Hit);

    if (Hit.bBlockingHit)
    {
        APawn* const MyPawn = GetPawn();
        if (MyPawn)
        {
            FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(
                MyPawn->GetActorLocation(),
                FVector(Hit.Location.X, Hit.Location.Y, MyPawn->GetActorLocation().Z)
            );

            FRotator NewRotation = FMath::RInterpTo(
                MyPawn->GetActorRotation(),
                TargetRotation,
                GetWorld()->GetDeltaSeconds(),
                20.0f
            );

            MyPawn->SetActorRotation(NewRotation);
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
        if (!PlayerCharacter->bIsLocked)
        {
            PlayerCharacter->ComboAttack();
        }
    }
}

void ASW_PlayerController::JumpAttack(const FInputActionValue& InputValue)
{
    if (ASW_CharacterBase* PlayerCharacter = Cast<ASW_CharacterBase>(GetPawn()))
    {
        if (!PlayerCharacter->bIsLocked)
        {
            PlayerCharacter->JumpAttack();
        }
    }
}

void ASW_PlayerController::NormalSkill(const FInputActionValue& InputValue)
{
    if (ASW_CharacterBase* PlayerCharacter = Cast<ASW_CharacterBase>(GetPawn()))
    {
        if (!PlayerCharacter->bIsLocked)
        {
            PlayerCharacter->NormalSkill();
        }
    }
}

void ASW_PlayerController::SpecialSkill(const FInputActionValue& InputValue)
{
    if (ASW_CharacterBase* PlayerCharacter = Cast<ASW_CharacterBase>(GetPawn()))
    {
        if (!PlayerCharacter->bIsLocked)
        {
            PlayerCharacter->SpecialSkill();
        }
    }
}

void ASW_PlayerController::DashSkill(const FInputActionValue& InputValue)
{
    if (ASW_CharacterBase* PlayerCharacter = Cast<ASW_CharacterBase>(GetPawn()))
    {
        if (!PlayerCharacter->bIsLocked)
        {
            PlayerCharacter->DashSkill();
        }
    }
}