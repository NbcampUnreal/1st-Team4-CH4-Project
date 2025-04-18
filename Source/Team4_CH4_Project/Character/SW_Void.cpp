#include "SW_Void.h"
#include "SW_Magic.h"
#include "SW_VoidSpawnActor.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "NiagaraComponent.h"
#include "UObject/ConstructorHelpers.h"

ASW_Void::ASW_Void()
{
    // 리플리케이션 용
    bReplicates = true;
    SetReplicateMovement(true);
    CharacterType = ECharacterType::Void;

    // 스탯 초기 설정 
    MaxHealth = 450;
    Health = MaxHealth;

    // 기본 데미지
    AttackDamage = 30.f;


    // 애니메이션 몽타주 초기화 (콤보 공격용)
    static ConstructorHelpers::FObjectFinder<UAnimMontage> Combo1(TEXT("/Game/Characters/Void/Animation/ComboAttack/AM_Void_Combo1.AM_Void_Combo1"));
    static ConstructorHelpers::FObjectFinder<UAnimMontage> Combo2(TEXT("/Game/Characters/Void/Animation/ComboAttack/AM_Void_Combo2.AM_Void_Combo2"));
    static ConstructorHelpers::FObjectFinder<UAnimMontage> Combo3(TEXT("/Game/Characters/Void/Animation/ComboAttack/AM_Void_Combo3.AM_Void_Combo3"));
    if (Combo1.Succeeded())
    {
        SkillMontages.Add(FName("Combo1"), Combo1.Object);
        ComboMontages.Add(Combo1.Object);
    }
    if (Combo2.Succeeded())
    {
        SkillMontages.Add(FName("Combo2"), Combo2.Object);
        ComboMontages.Add(Combo2.Object);
    }
    if (Combo3.Succeeded())
    {
        SkillMontages.Add(FName("Combo3"), Combo3.Object);
        ComboMontages.Add(Combo3.Object);
    }

    // 콤보
    FSkillData Combo1Data;
    Combo1Data.DamageMultiplier = 1.0f;
    Combo1Data.AttackType = ESkillAttackType::RangedProjectile;
    Combo1Data.Range = FVector(100.f); // 의미 없음. 투사체 방식
    Combo1Data.Offset = FVector(100.f, 0.f, 0.f);
    Combo1Data.ProjectileClass = ComboProjectileClass; // 던지는 액터

    SkillDataMap.Add("Combo1", Combo1Data);
    SkillDataMap.Add("Combo2", Combo1Data);
    SkillDataMap.Add("Combo3", Combo1Data);

    // 대쉬 스킬 데이터 초기화
    FSkillData DashSkillData;
    DashSkillData.DamageMultiplier = 0.8;
    DashSkillData.AttackType = ESkillAttackType::MeleeSphere;
    DashSkillData.Range = FVector(300.f); // 대시 범위: 반경 300
    DashSkillData.Offset = FVector(250.f, 0.f, 0.f); // 캐릭터 앞쪽
    SkillDataMap.Add(FName("DashSkill"), DashSkillData);

    // 궁극기 스킬 데이터 초기화
    FSkillData SpecialSkillData;
    SpecialSkillData.DamageMultiplier = 1.f;
    SpecialSkillData.AttackType = ESkillAttackType::MeleeSphere;
    SpecialSkillData.Range = FVector(1000.f);
    SpecialSkillData.Offset = FVector(1000.f, 0.f, 0.f);
    SkillDataMap.Add(FName("SpecialSkill"), SpecialSkillData);
}

void ASW_Void::BeginPlay()
{
    Super::BeginPlay();
}
// ============================================= 콤보어택 =============================================

void ASW_Void::ComboAttack()
{
    Super::ComboAttack();
}

void ASW_Void::SpawnComboMagic()
{
    if (!HasAuthority() || !ComboProjectileClass) return;

    FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 100.f;
    FRotator SpawnRotation = GetActorRotation();

    FActorSpawnParameters Params;
    Params.Owner = this;
    Params.Instigator = this;

    AActor* Projectile = GetWorld()->SpawnActor<AActor>(ComboProjectileClass, SpawnLocation, SpawnRotation, Params);
    if (ASW_Magic* Magic = Cast<ASW_Magic>(Projectile))
    {
        Magic->Damage = AttackDamage * (CurrentComboIndex + 1);
      
        if (CurrentComboIndex == 1)
        {
            Magic->SetActorScale3D(FVector(1.2f)); // 1.2배 크기
        }
        else if (CurrentComboIndex == 2)
        {
            Magic->SetActorScale3D(FVector(1.5f)); // 1.5배 크기
        }
    }
}
// ============================================= 노멀스킬 =============================================
void ASW_Void::NormalSkill()
{
    PlaySkillAnimation(FName("NormalSkill"));
}

void ASW_Void::SpawnNormalMagic()
{
    if (!HasAuthority() || !NormalProjectileClass) return;

    FVector Direction = GetActorForwardVector();
    FVector SpawnLocation = GetActorLocation() + Direction * 100.f;
    FRotator SpawnRotation = Direction.Rotation();

    FActorSpawnParameters Params;
    Params.Owner = this;
    Params.Instigator = this;

    AActor* Projectile = GetWorld()->SpawnActor<AActor>(NormalProjectileClass, SpawnLocation, SpawnRotation, Params);
    if (ASW_Magic* Magic = Cast<ASW_Magic>(Projectile))
    {
        Magic->Damage = AttackDamage * 3.f;
    }
}
// ===================================================================================================






// =============================================점프어택 =============================================
void ASW_Void::JumpAttack()
{
    if (!HasAuthority() || bIsLocked || bIsJumpAttacking) return;

    bIsJumpAttacking = true;

    PlaySkillAnimation(FName("JumpAttack"));

    FVector Forward = GetActorForwardVector().GetSafeNormal();
    float DashSpeed = 1300.f;

    UCharacterMovementComponent* MoveComp = GetCharacterMovement();
    MoveComp->BrakingFrictionFactor = 0.f;
    MoveComp->BrakingDecelerationWalking = 0.f;

    LaunchCharacter(Forward * DashSpeed, true, true);

    // 체력 회복
    Health = FMath::Clamp(Health + 25.f, 0.f, MaxHealth);
    UpdateHealthBar();

    // 낙하 후 마찰 원복
    FTimerHandle ResetHandle;
    GetWorldTimerManager().SetTimer(ResetHandle, FTimerDelegate::CreateLambda([this, MoveComp]()
        {
            MoveComp->BrakingFrictionFactor = 2.f;
            MoveComp->BrakingDecelerationWalking = 2048.f;
        }), 0.5f, false);
    FTimerHandle JumpAttackFlagTimerHandle;
    // 0.5초 후 점프어택 플래그 해제
    GetWorldTimerManager().SetTimer(JumpAttackFlagTimerHandle, FTimerDelegate::CreateLambda([this]()
        {
            bIsJumpAttacking = false;
        }), 0.5f, false);
}

// ===================================================================================================




// ============================================= 대쉬스킬 =============================================

void ASW_Void::DashSkill()
{
    PlaySkillAnimation(FName("DashSkill"));
}

void ASW_Void::ExecuteDashTeleport()
{
    if (!HasAuthority()) return;  // 서버에서만 실행

    FVector TeleportLocation = GetActorLocation() + GetActorForwardVector() * 300.f;
    TeleportLocation.Z = GetActorLocation().Z;

    TeleportTo(TeleportLocation, GetActorRotation());
}
// ====================================================================================================




// ============================================= 스페셜스킬 ============================================
void ASW_Void::SpecialSkill()
{
    if (!HasAuthority() || !VoidUltimateActorClass) return;

    PlaySkillAnimation(FName("SpecialSkill"));

    // 스폰 위치와 회전 설정
    FVector ForwardVector = GetActorForwardVector();
    FVector InitialSpawnLocation = GetActorLocation() + ForwardVector * 1000.f;
    FRotator SpawnRotation = ForwardVector.Rotation();

    // 1.35초 후 스폰
    FTimerHandle SpawnTimerHandle;
    GetWorldTimerManager().SetTimer(SpawnTimerHandle, FTimerDelegate::CreateLambda(
        [this, InitialSpawnLocation, SpawnRotation]()
        {
            FActorSpawnParameters Params;
            Params.Owner = this;
            Params.Instigator = this;
            Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

            ASW_VoidSpawnActor* Spawned = GetWorld()->SpawnActor<ASW_VoidSpawnActor>(
                VoidUltimateActorClass,
                InitialSpawnLocation,
                SpawnRotation,
                Params);

            if (Spawned)
            {
                Spawned->OwnerCharacter = this;
                Spawned->Damage = AttackDamage * 5;
                Spawned->DamageMultiplier = 1.f;
                Spawned->Range = FVector(1000.f);
                Spawned->Offset = FVector::ZeroVector;
            }
        }), 1.35f, false);
}
// ===================================================================================================
