#include "SW_CharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"
#include "SW_PlayerAnimInstance.h"
#include "SW_PlayerAnimLayerInterface.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/DamageEvents.h"
#include "Game/GameMode/SW_GameMode.h"
#include "Game/GameState/SW_GameState.h"
#include "Character/Player/SW_PlayerState.h"
#include "UI/SW_HUDManager.h"
#include "UI/ViewModels/SW_PlayerInfoViewModel.h"
#include "UI/ViewModels/SW_SkillViewModel.h"
#include "UI/ViewModels/SW_LevelExpViewModel.h"

ASW_CharacterBase::ASW_CharacterBase()
{
    // 리플리케이션 용
    bReplicates = true;
    SetReplicateMovement(true);

    PrimaryActorTick.bCanEverTick = true;

    bUseControllerRotationPitch = false;
    bUseControllerRotationRoll = false;
    bUseControllerRotationYaw = false;

    // 그림자 Off
    if (GetMesh())
    {
        GetMesh()->CastShadow = false;
        GetMesh()->bCastDynamicShadow = false;
        GetMesh()->bAffectDistanceFieldLighting = false;
    }

    if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
    {
        MoveComp->bOrientRotationToMovement = true;
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
    CameraBoom->bDoCollisionTest = false;

    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom);
    FollowCamera->bUsePawnControlRotation = false;

    HealthBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));
    HealthBarWidget->SetupAttachment(GetMesh());
    HealthBarWidget->SetRelativeLocation(FVector(0.f, 0.f, 280.f));
    HealthBarWidget->SetRelativeRotation(FRotator(180.f, 0.f, 0.f));
    HealthBarWidget->SetUsingAbsoluteRotation(true);
    HealthBarWidget->SetWidgetSpace(EWidgetSpace::World);
    HealthBarWidget->SetDrawSize(FVector2D(200.f, 20.f));
    HealthBarWidget->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    HealthBarWidget->SetGenerateOverlapEvents(false);
    HealthBarWidget->SetCastShadow(false);
    HealthBarWidget->bCastDynamicShadow = false;
    HealthBarWidget->bAffectDistanceFieldLighting = false;

    bIsLocked = false;
    CurrentComboIndex = 0;
 
    // MaxHealth 초기화 (자식 클래스에서 설정 가능하도록 기본값)
    MaxHealth = 100;
    Health = MaxHealth;
}

void ASW_CharacterBase::BeginPlay()
{
    Super::BeginPlay();
    UpdateHealthBar();
}

void ASW_CharacterBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    AccelerationLastFrame = Acceleration;
    Acceleration = GetCharacterMovement()->GetCurrentAcceleration();
    VelocityLastFrame = Velocity;
    Velocity = GetCharacterMovement()->Velocity;

    // 프레임마다 데미지 중복 방지용
    SkillsAppliedThisFrame.Empty();
}

void ASW_CharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
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

void ASW_CharacterBase::ComboAttack()
{
    if (!ComboMontages.IsValidIndex(CurrentComboIndex)) return;

    FString ComboKey = FString::Printf(TEXT("Combo%d"), CurrentComboIndex + 1);
    FSkillData* SkillData = SkillDataMap.Find(*ComboKey);
    if (!SkillData) return;

    PlayAnimMontage(ComboMontages[CurrentComboIndex]);
    SetLockedState(true);
}

void ASW_CharacterBase::JumpAttack()
{
    ActivateSkill(ESkillType::Skill3, DropSkillDownTime);
}
void ASW_CharacterBase::NormalSkill()
{
    ActivateSkill(ESkillType::Skill1, NormalSkillDownTime);
}

void ASW_CharacterBase::SpecialSkill()
{
    ActivateSkill(ESkillType::Skill2, SpecialSkillDownTime);
}

void ASW_CharacterBase::DashSkill()
{
    ActivateSkill(ESkillType::Dash, DashSkillDownTime);
}

TArray<AActor*> ASW_CharacterBase::GetTargetsInRange_Implementation(FName SkillName)
{
    TArray<AActor*> HitActors;
    TArray<AActor*> ActorsToIgnore;
    ActorsToIgnore.Add(this);

    const FSkillData* SkillData = SkillDataMap.Find(SkillName);
    if (!SkillData) return HitActors;

    FVector Location = GetActorLocation() + GetActorRotation().RotateVector(SkillData->Offset);

    switch (SkillData->AttackType)
    {
    case ESkillAttackType::MeleeSphere:
    {
        float Radius = SkillData->Range.X;

        // 디버그용
        DrawDebugSphere(GetWorld(), Location, Radius, 12, FColor::Green, false, 1.0f);

        UKismetSystemLibrary::SphereOverlapActors(
            GetWorld(),
            Location,
            Radius,
            TArray<TEnumAsByte<EObjectTypeQuery>>{ UEngineTypes::ConvertToObjectType(ECC_Pawn) },
            ACharacter::StaticClass(),
            ActorsToIgnore,
            HitActors
        );
        break;
    }

    case ESkillAttackType::MeleeBox:
    {
        FVector Extent = SkillData->Range;

        // 디버그용
        DrawDebugBox(GetWorld(), Location, Extent, GetActorQuat(), FColor::Cyan, false, 1.f);

        UKismetSystemLibrary::BoxOverlapActors(
            GetWorld(),
            Location,
            Extent,
            TArray<TEnumAsByte<EObjectTypeQuery>>{ UEngineTypes::ConvertToObjectType(ECC_Pawn) },
            ACharacter::StaticClass(),
            ActorsToIgnore,
            HitActors
        );
        break;
    }

    case ESkillAttackType::BoxTrace:
    {
        FVector Start = GetActorLocation() + GetActorRotation().RotateVector(SkillData->Offset);
        FVector End = Start + GetActorForwardVector() * 50.f; // 캐릭터 제외 위해 50 정도 앞으로 이동

        FVector HalfSize = SkillData->Range * 0.5f;
        FQuat Rotation = GetActorQuat();

        TArray<FHitResult> HitResults;
        FCollisionShape BoxShape = FCollisionShape::MakeBox(HalfSize);
        FCollisionQueryParams Params;
        Params.AddIgnoredActor(this);

        bool bHit = GetWorld()->SweepMultiByChannel(
            HitResults,
            Start,
            End,
            Rotation,
            ECC_Pawn,
            BoxShape,
            Params
        );

        // 디버그 박스
        DrawDebugBox(GetWorld(), Start, HalfSize, Rotation, FColor::Purple, false, 1.5f, 0, 2.0f);

        if (bHit)
        {
            for (const FHitResult& Hit : HitResults)
            {
                if (AActor* HitActor = Hit.GetActor())
                {
                    HitActors.AddUnique(HitActor);
                }
            }
        }

        break;
    }

    case ESkillAttackType::RangedTrace:
    {
        FVector Start = Location;
        FVector End = Start + GetActorForwardVector() * SkillData->Range.X;
        FHitResult HitResult;

        // 디버그용
        DrawDebugLine(GetWorld(), Start, End, FColor::Blue, false, 1.0f, 0, 2.0f);

        UKismetSystemLibrary::LineTraceSingle(
            GetWorld(),
            Start,
            End,
            UEngineTypes::ConvertToTraceType(ECC_Pawn),
            false,
            ActorsToIgnore,
            EDrawDebugTrace::None,
            HitResult,
            true
        );

        if (HitResult.bBlockingHit && HitResult.GetActor())
        {
            HitActors.Add(HitResult.GetActor());
        }
        break;
    }

    case ESkillAttackType::RangedProjectile:
    {
        // 디버그용
        DrawDebugSphere(GetWorld(), Location, 20.f, 8, FColor::Yellow, false, 1.0f);

        if (SkillData->ProjectileClass)
        {
            FActorSpawnParameters SpawnParams;
            SpawnParams.Owner = this;
            SpawnParams.Instigator = GetInstigator();

            AActor* Projectile = GetWorld()->SpawnActor<AActor>(
                SkillData->ProjectileClass,
                Location,
                GetActorRotation(),
                SpawnParams
            );
        }
        break;
    }

    default:
        break;
    }

    return HitActors;
}

void ASW_CharacterBase::ApplySkillDamage(FName SkillName, const TArray<AActor*>& Targets)
{
    const FSkillData* SkillData = SkillDataMap.Find(SkillName);
    if (!SkillData) return;

    float FinalDamage = AttackDamage * SkillData->DamageMultiplier;

    for (AActor* Target : Targets)
    {
        if (Target && Target != this)
        {
            FDamageEvent DamageEvent;
            Target->TakeDamage(FinalDamage, DamageEvent, GetController(), this);
        }
    }
}

void ASW_CharacterBase::PlaySkillAnimation(FName SkillName)
{
    if (bIsLocked) return;

    UAnimMontage** MontagePtr = SkillMontages.Find(SkillName);
    if (MontagePtr && *MontagePtr)
    {
        PlayAnimMontage(*MontagePtr);
        return;
    }

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

void ASW_CharacterBase::SetLockedState(bool bLocked)
{
    bIsLocked = bLocked;
    if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
    {
        MoveComp->MaxWalkSpeed = bLocked ? 0.f : DefaultMoveSpeed;
    }
}

void ASW_CharacterBase::SetMovementLocked(bool bLocked)
{
    bIsMovementLocked = bLocked;
    if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
    {
        MoveComp->MaxWalkSpeed = bLocked ? 0.f : DefaultMoveSpeed;
    }
}

void ASW_CharacterBase::AdvanceCombo()
{
    CurrentComboIndex++;
    if (!ComboMontages.IsValidIndex(CurrentComboIndex))
    {
        ResetCombo();
        return;
    }

    PlayAnimMontage(ComboMontages[CurrentComboIndex]);
    SetLockedState(true);
}

void ASW_CharacterBase::ResetCombo()
{
    CurrentComboIndex = 0;
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
    // 무적 상태면 데미지 X
    if (bIsInvincible)
        return 0.f;

    int32 DamageToApply = FMath::Clamp(FMath::RoundToInt(DamageAmount), 0, Health);
    if (DamageToApply <= 0) return 0.f;

    Health -= DamageToApply;
    UpdateHealthBar();

    // 공격당하면 카메라가 바라보고있는곳으로 이펙트 생성(캐릭터 중앙에)
    if (HitEffect)
    {
        FVector SpawnLocation = GetActorLocation() + FVector(0.f, 0.f, 80.f);

        if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
        {
            if (APlayerCameraManager* CamMgr = PC->PlayerCameraManager)
            {
                FRotator CameraRot = CamMgr->GetCameraRotation();
                FRotator SpawnRotation = FRotator(0.f, CameraRot.Yaw, 0.f);

                UNiagaraFunctionLibrary::SpawnSystemAtLocation(
                    GetWorld(),
                    HitEffect,
                    SpawnLocation,
                    SpawnRotation
                );
            }
        }
    }

    if (Health <= 0)
    {
        Health = 0;
        SetLockedState(true);
        if (DeathMontage)
        {
            PlayAnimMontage(DeathMontage);
        }
        Server_ExecuteDeath_Implementation(DamageCauser);
        CharacterDeath();
        SetLifeSpan(2.f);
    }
    else if (HitReactionMontage && !bIsLocked)
    {
        PlayAnimMontage(HitReactionMontage);
    }

    return DamageToApply;
}

void ASW_CharacterBase::CharacterDeath()
{
    bIsDead = true;
    if (ASW_GameState* SWGS = Cast<ASW_GameState>(GetWorld()->GetGameState()))
    {
        SWGS->SetCurrentPlayerAmount(-1);
        
        if (ASW_PlayerController* ThisPC = this->GetController<ASW_PlayerController>())
        {
            SWGS->AddRanking(ThisPC);
        }
    }
    if (ASW_PlayerState* ThisPS = this->GetPlayerState<ASW_PlayerState>())
    {
        UE_LOG(LogTemp, Warning, TEXT("Working"));
        ThisPS->SetbIsWon(false);
    }
}

void ASW_CharacterBase::Server_ExecuteDeath_Implementation(AActor* Killer)
{
    if (Killer)
    {
        if (AController* KillerController = Killer->GetInstigatorController())
        {
            if (ASW_PlayerController* KillerPC = Cast<ASW_PlayerController>(KillerController))
            {
                if (ASW_PlayerState* KillerPS = KillerPC->GetPlayerState<ASW_PlayerState>())
                {
                    KillerPS->SetPlayerKill(1);
                }
            }
        }
    }
}

void ASW_CharacterBase::Server_PlaySkill_Implementation(FName SkillName)
{
    if (bIsLocked) return;
    if (SkillName == "ComboAttack")
    {
        ComboAttack();
        Multicast_ComboAttack();
    }
    else if (SkillName == "JumpAttack")
    {
        if (!GetCharacterMovement()->IsFalling() || bIsJumpAttacking) return;
        JumpAttack();
        Multicast_PlaySkill(SkillName);
    }
    else if (SkillName == "DashSkill")
    {
        DashSkill();
        Multicast_PlaySkill(SkillName);
    }
    else if (SkillName == "NormalSkill")
    {
        NormalSkill();
        Multicast_PlaySkill(SkillName);
    }
    else if (SkillName == "SpecialSkill")
    {
        SpecialSkill();
        Multicast_PlaySkill(SkillName);
    }
}
void ASW_CharacterBase::Multicast_PlaySkill_Implementation(FName SkillName)
{
    // DedicatedServer 제외 + 서버 자신 제외
    if (!IsNetMode(NM_DedicatedServer) && !HasAuthority())
    {
        PlaySkillAnimation(SkillName);
    }
}

// 리플리케이션되는 함수들================================================================================

void ASW_CharacterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ASW_CharacterBase, Health);
    DOREPLIFETIME(ASW_CharacterBase, bIsLocked);
    DOREPLIFETIME(ASW_CharacterBase, bIsAttacking);
    DOREPLIFETIME(ASW_CharacterBase, bIsMovementLocked);
    DOREPLIFETIME(ASW_CharacterBase, bIsDead);
    DOREPLIFETIME(ASW_CharacterBase, bCanUseNormalSkill);
    DOREPLIFETIME(ASW_CharacterBase, bCanUseSpecialSkill);
    DOREPLIFETIME(ASW_CharacterBase, bCanUseDropSkill);
    DOREPLIFETIME(ASW_CharacterBase, bCanUseDashSkill);
}

void ASW_CharacterBase::ActivateSkill(ESkillType skillType, float _DownTime)
{
    Client_UpdateSkillAvailability(skillType);
    switch (skillType)
    {
    case ESkillType::Skill1:
        if (bCanUseNormalSkill)
        {
            PlaySkillAnimation(FName("NormalSkill"));
            Client_SetSkillDown(skillType);
        }
        break;
    case ESkillType::Skill2:
        if (bCanUseSpecialSkill)
        {
            PlaySkillAnimation(FName("SpecialSkill"));
            Client_SetSkillDown(skillType);
        }
        break;
    case ESkillType::Skill3:
        if (bCanUseDropSkill)
        {
            PlaySkillAnimation(FName("JumpAttack"));
            Client_SetSkillDown(skillType);
        }
        break;
    case ESkillType::Dash:
        if (bCanUseDashSkill)
        {
            PlaySkillAnimation(FName("DashSkill"));
            Client_SetSkillDown(skillType);
        }
    }
}

void ASW_CharacterBase::OnRep_Health()
{
    UpdateHealthBar();
}


void ASW_CharacterBase::Server_ApplySkillDamage_Implementation(FName SkillName)
{
    if (!HasAuthority()) return;
    if (SkillsAppliedThisFrame.Contains(SkillName)) return;
    SkillsAppliedThisFrame.Add(SkillName);

    TArray<AActor*> Targets = GetTargetsInRange(SkillName);
    ApplySkillDamage(SkillName, Targets);
    Multicast_ApplySkillDamage(SkillName);
}

void ASW_CharacterBase::Multicast_ApplySkillDamage_Implementation(FName SkillName)
{
    if (!IsLocallyControlled()) return;
    PlaySkillAnimation(SkillName); // 클라이언트는 애니메이션만
}

void ASW_CharacterBase::Multicast_ComboAttack_Implementation()
{
    if (!HasAuthority())
    {
        ComboAttack();
    }
}
// ============================================================================================

void ASW_CharacterBase::Client_UpdateSkillAvailability_Implementation(ESkillType InSkillType)
{
    if (UGameInstance* GI = GetGameInstance())
    {
        if (USW_HUDManager* HUDManager = GI->GetSubsystem<USW_HUDManager>())
        {
            USW_SkillViewModel* SkillViewModel = Cast<USW_SkillViewModel>(HUDManager->GetViewModel(EViewModelType::SkillViewModel));
            if (SkillViewModel)
            {
                switch (InSkillType)
                {
                case ESkillType::Skill1:
                    Server_UpdateSkillAvailability(InSkillType, SkillViewModel->GetSkill1Time() <= 0);
                    break;
                case ESkillType::Skill2:
                    Server_UpdateSkillAvailability(InSkillType, SkillViewModel->GetSkill2Time() <= 0);
                    break;
                case ESkillType::Skill3:
                    Server_UpdateSkillAvailability(InSkillType, SkillViewModel->GetSkill3Time() <= 0);
                    break;
                case ESkillType::Dash:
                    Server_UpdateSkillAvailability(InSkillType, SkillViewModel->GetDashTime() <= 0);
                    break;
                }
            }
        }
    }
}

void ASW_CharacterBase::Server_UpdateSkillAvailability_Implementation(ESkillType InSkillType, bool bCanUse)
{
    switch (InSkillType)
    {
    case ESkillType::Skill1:
        bCanUseNormalSkill = bCanUse;
        break;
    case ESkillType::Skill2:
        bCanUseSpecialSkill = bCanUse;
        break;
    case ESkillType::Skill3:
        bCanUseDropSkill = bCanUse;
        break;
    case ESkillType::Dash:
        bCanUseDashSkill = bCanUse;
        break;
    }
}

void ASW_CharacterBase::Client_SetSkillDown_Implementation(ESkillType InSkillType)
{
    if (UGameInstance* GI = GetGameInstance())
    {
        if (USW_HUDManager* HUDManager = GI->GetSubsystem<USW_HUDManager>())
        {
            USW_SkillViewModel* SkillViewModel = Cast<USW_SkillViewModel>(HUDManager->GetViewModel(EViewModelType::SkillViewModel));
            if (SkillViewModel)
            {
                switch (InSkillType)
                {
                case ESkillType::Skill1:
                    SkillViewModel->SetSkill1Time(NormalSkillDownTime);
                    break;
                case ESkillType::Skill2:
                    SkillViewModel->SetSkill2Time(SpecialSkillDownTime);
                    break;
                case ESkillType::Skill3:
                    SkillViewModel->SetSkill3Time(DropSkillDownTime);
                    break;
                case ESkillType::Dash:
                    SkillViewModel->SetDashTime(DashSkillDownTime);
                }
            }
        }
    }
}


