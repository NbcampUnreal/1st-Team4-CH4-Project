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
        // 캐릭터 이동방향에 맞춰서 캐릭터 이동 true
        MoveComp->bOrientRotationToMovement = true;

        MoveComp->MaxWalkSpeed = 600.f;
        MoveComp->BrakingDecelerationWalking = 2048.f;
        MoveComp->GroundFriction = 8.f;
        MoveComp->MaxAcceleration = 2048.f;
        MoveComp->BrakingFrictionFactor = 2.f;
        MoveComp->BrakingFriction = 8.f;
    }

    //스프링암
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 1400.f;
    CameraBoom->SetRelativeRotation(FRotator(-40.f, 0.f, 0.f));
    CameraBoom->bUsePawnControlRotation = false;
    CameraBoom->bInheritYaw = false;
    CameraBoom->bInheritPitch = false;
    CameraBoom->bInheritRoll = false;
    CameraBoom->bDoCollisionTest = false; // 스프링암사이에 사물이나 캐릭터가 겹쳐도 거리 유지

    // 카메라
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom);
    FollowCamera->bUsePawnControlRotation = false;

    // =======================체력바==============================================
   HealthBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));
   HealthBarWidget->SetupAttachment(GetMesh());
   HealthBarWidget->SetRelativeLocation(FVector(0.f, 0.f, 280.f));        // 머리 위 고정
   HealthBarWidget->SetRelativeRotation(FRotator(180.f, 0.f, 0.f));       // 회전값 180으로 고정
   HealthBarWidget->SetUsingAbsoluteRotation(true);                       // 부모 회전 무시
   HealthBarWidget->SetWidgetSpace(EWidgetSpace::World);                  // 월드기준
   HealthBarWidget->SetDrawSize(FVector2D(200.f, 20.f));
   HealthBarWidget->SetCollisionEnabled(ECollisionEnabled::NoCollision);  // 충돌 제거
   HealthBarWidget->SetGenerateOverlapEvents(false);
   HealthBarWidget->SetCastShadow(false);                                 // 그림자 제거
   HealthBarWidget->bCastDynamicShadow = false;
   HealthBarWidget->bAffectDistanceFieldLighting = false;
   // =====================================================================++++++++

    // 스킬, 콤보용 변수 초기화
    bIsLocked = false;
    CurrentComboIndex = 0;
    bCanNextCombo = true;
    bPendingNextCombo = false;
}

void ASW_CharacterBase::BeginPlay()
{
    Super::BeginPlay();

    // 체력바 초기화
    UpdateHealthBar();
}

void ASW_CharacterBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (HealthBarWidget)
    {
        FVector CameraLocation = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraLocation();
        FVector ToCamera = CameraLocation - HealthBarWidget->GetComponentLocation();
        FRotator LookAtRotation = FRotationMatrix::MakeFromX(ToCamera).Rotator();

        LookAtRotation.Pitch = 0.f;
        LookAtRotation.Roll = 0.f;
    }

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
            GetWorldTimerManager().SetTimer(
                ComboResetTimer,
                this,
                &ASW_CharacterBase::CheckPendingCombo,
                MontageDuration * 0.8f,
                false
            );
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
        MoveComp->MaxWalkSpeed = bLocked ? 0.f : DefaultMoveSpeed;
    }
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

void ASW_CharacterBase::ResetCombo()
{
    CurrentComboIndex = 0;
    bCanNextCombo = true;
    bPendingNextCombo = false;
    SetLockedState(false);
}

void ASW_CharacterBase::UpdateHealthBar()
{
    if (!HealthBarWidget) return;

    USW_HP* HP = Cast<USW_HP>(HealthBarWidget->GetUserWidgetObject());
    if (HP)
    {
        HP->UpdateHealthBar(Health, MaxHealth);
    }
}

float ASW_CharacterBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    const int32 DamageToApply = FMath::Clamp(FMath::RoundToInt(DamageAmount), 0, Health);
    if (DamageToApply <= 0) return 0.f;

    Health -= DamageToApply;

    // 체력바 UI 업데이트
    UpdateHealthBar();

    // 사망이 아닐 경우 피격 처리
    if (Health > 0)
    {
        // 피격 애니메이션 재생
        if (HitReactionMontage && !bIsLocked)
        {
            PlayAnimMontage(HitReactionMontage);
        }

        // 넉백 처리 (이동만 물리적으로)
        if (DamageCauser)
        {
            FVector KnockbackDir = (GetActorLocation() - DamageCauser->GetActorLocation()).GetSafeNormal();
            LaunchCharacter(KnockbackDir * 500.f + FVector(0.f, 0.f, 200.f), true, true);
        }
    }
    else
    {
        // 체력 최소값 보정
        Health = 0;

        // 사망 애니메이션
        SetLockedState(true); // 이동/입력 잠금
        if (DeathMontage)
        {
            PlayAnimMontage(DeathMontage);
        }

        // TODO: 사망 후 파괴 or 리스폰 처리 (필요시 타이머로 처리 가능)
    }

    return DamageToApply;
}
