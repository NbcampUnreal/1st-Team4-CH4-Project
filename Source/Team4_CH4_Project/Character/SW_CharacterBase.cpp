#include "SW_CharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"
#include "SW_PlayerAnimInstance.h"
#include "SW_PlayerAnimLayerInterface.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ASW_CharacterBase::ASW_CharacterBase()
{
    PrimaryActorTick.bCanEverTick = true;

    bUseControllerRotationPitch = false;
    bUseControllerRotationRoll = false;
    bUseControllerRotationYaw = false;

    if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
    {
        MoveComp->bOrientRotationToMovement = false;
        MoveComp->MaxWalkSpeed = 600.f;
        MoveComp->BrakingDecelerationWalking = 2048.f;
        MoveComp->GroundFriction = 8.f;
        MoveComp->MaxAcceleration = 2048.f;
        MoveComp->BrakingFrictionFactor = 2.f;
        MoveComp->BrakingFriction = 8.f;
    }

    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 1400.f;
    CameraBoom->SetRelativeRotation(FRotator(-40.f, 0.f, 0.f));
    CameraBoom->bUsePawnControlRotation = false;
    CameraBoom->bInheritYaw = false;
    CameraBoom->bInheritPitch = false;
    CameraBoom->bInheritRoll = false;

    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom);
    FollowCamera->bUsePawnControlRotation = false;

    bIsLocked = false;
    CurrentComboIndex = 0;
    bCanNextCombo = true;
    bPendingNextCombo = false;
}

void ASW_CharacterBase::BeginPlay()
{
    Super::BeginPlay();
}

void ASW_CharacterBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    AccelerationLastFrame = Acceleration;
    Acceleration = GetCharacterMovement()->GetCurrentAcceleration();
    VelocityLastFrame = Velocity;
    Velocity = GetCharacterMovement()->Velocity;
}

void ASW_CharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ASW_CharacterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(ASW_CharacterBase, Health);
    DOREPLIFETIME(ASW_CharacterBase, Stamina);
}

void ASW_CharacterBase::Player_Move(const FInputActionValue& _InputValue)
{
    if (bIsLocked) return;

    const FVector2D MoveVector = _InputValue.Get<FVector2D>();
    if (MoveVector.IsNearlyZero()) return;

    FRotator ControlRotation = GetControlRotation();
    FRotator YawRotation(0, ControlRotation.Yaw, 0);
    FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
    FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
    AddMovementInput(ForwardDirection, MoveVector.Y);
    AddMovementInput(RightDirection, MoveVector.X);
}

void ASW_CharacterBase::Player_Jump(const FInputActionValue& _InputValue)
{
    if (bIsLocked) return;

    bool IsJump = _InputValue.Get<bool>();
    if (IsJump) Jump();
}

// 평타 3타 콤보
void ASW_CharacterBase::ComboAttack()
{
    if (!GetMesh() || !ComboMontages.IsValidIndex(CurrentComboIndex)) return;

    if (bCanNextCombo)
    {
        UAnimMontage* MontageToPlay = ComboMontages[CurrentComboIndex];
        if (MontageToPlay)
        {
            PlayAnimMontage(MontageToPlay);
            bCanNextCombo = false;

            FTimerHandle ComboResetTimer;

            float MontageDuration = MontageToPlay->GetPlayLength();
            GetWorldTimerManager().SetTimer(ComboResetTimer, this, &ASW_CharacterBase::CheckPendingCombo, MontageDuration * 0.5f, false);
        }
    }
    else // 평타 도중에 키입력시
    {
        bPendingNextCombo = true;
    }
}

void ASW_CharacterBase::JumpAttack()
{
    PlaySkillAnimation(FName("JumpAttack"));
}

void ASW_CharacterBase::NormalSkill()
{
    PlaySkillAnimation(FName("NormalSkill"));
}

void ASW_CharacterBase::SpecialSkill()
{
    PlaySkillAnimation(FName("SpecialSkill"));
}

void ASW_CharacterBase::DashSkill()
{
    PlaySkillAnimation(FName("DashSkill"));
}

void ASW_CharacterBase::PlaySkillAnimation(FName SkillName)
{
    if (bIsLocked) return;

    UAnimMontage** MontagePtr = SkillMontages.Find(SkillName);
    if (MontagePtr && *MontagePtr)
    {
        PlayAnimMontage(*MontagePtr);
    }
    else
    {
        if (USW_PlayerAnimInstance* Anim = Cast<USW_PlayerAnimInstance>(GetMesh()->GetAnimInstance()))
        {
            if (Anim->Implements<USW_PlayerAnimLayerInterface>())
            {
                if (SkillName == FName("JumpAttack"))
                    ISW_PlayerAnimLayerInterface::Execute_PlayJumpAttack(Anim);
                else if (SkillName == FName("DashSkill"))
                    ISW_PlayerAnimLayerInterface::Execute_PlayDashSkill(Anim);
                else if (SkillName == FName("NormalSkill"))
                    ISW_PlayerAnimLayerInterface::Execute_PlayNormalSkill(Anim);
                else if (SkillName == FName("SpecialSkill"))
                    ISW_PlayerAnimLayerInterface::Execute_PlaySpecialSkill(Anim);
            }
        }
    }
}

void ASW_CharacterBase::SetLockedState(bool bLocked)
{
    bIsLocked = bLocked;
    if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
    {
        MoveComp->MaxWalkSpeed = bLocked ? 0.f : 600.f;
    }
}

float ASW_CharacterBase::GetGroundSpeed() { return GroundSpeed; }
void ASW_CharacterBase::SetGroundSpeed(float _GroundSpeed) { GroundSpeed = _GroundSpeed; }
bool ASW_CharacterBase::IsMoving() const { return Acceleration != FVector::ZeroVector && Velocity != FVector::ZeroVector; }
bool ASW_CharacterBase::IsJump() const { return InAir() && GetVelocity().Z > 0; }
bool ASW_CharacterBase::InAir() const { return GetCharacterMovement()->IsFalling(); }

void ASW_CharacterBase::ResetCombo()
{
    CurrentComboIndex = 0;
    bCanNextCombo = true;
    bPendingNextCombo = false;
    SetLockedState(false);
}

void ASW_CharacterBase::CheckPendingCombo()
{
    if (bPendingNextCombo)
    {
        bPendingNextCombo = false;
        CurrentComboIndex++;
        if (CurrentComboIndex >= 3)
        {
            ResetCombo();
            return;
        }

        bCanNextCombo = true;
        ComboAttack();
    }
    else
    {
        ResetCombo();
    }
}
