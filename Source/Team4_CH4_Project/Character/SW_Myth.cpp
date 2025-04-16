#include "SW_Myth.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "SW_MythSpawnActor.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/BoxComponent.h"

ASW_Myth::ASW_Myth()
{
    // 애니메이션 몽타주 초기화 (콤보 공격용)
    static ConstructorHelpers::FObjectFinder<UAnimMontage> Combo1(TEXT("/Game/Characters/Myth/Animation/ComboAttack/AM_Myth_Combo1.AM_Myth_Combo1"));
    static ConstructorHelpers::FObjectFinder<UAnimMontage> Combo2(TEXT("/Game/Characters/Myth/Animation/ComboAttack/AM_Myth_Combo2.AM_Myth_Combo2"));
    static ConstructorHelpers::FObjectFinder<UAnimMontage> Combo3(TEXT("/Game/Characters/Myth/Animation/ComboAttack/AM_Myth_Combo3.AM_Myth_Combo3"));
    if (Combo1.Succeeded()) ComboMontages.Add(Combo1.Object);
    if (Combo2.Succeeded()) ComboMontages.Add(Combo2.Object);
    if (Combo3.Succeeded()) ComboMontages.Add(Combo3.Object);

    if (Combo1.Succeeded())
    {
        ComboMontages.Add(Combo1.Object);
        SkillMontages.Add(FName("Combo1"), Combo1.Object);
    }
    if (Combo2.Succeeded())
    {
        ComboMontages.Add(Combo2.Object);
        SkillMontages.Add(FName("Combo2"), Combo2.Object);
    }
    if (Combo3.Succeeded())
    {
        ComboMontages.Add(Combo3.Object);
        SkillMontages.Add(FName("Combo3"), Combo3.Object);
    }


    // 스탯 초기화
    MaxHealth = 400;
    Health = MaxHealth;

    // 기본 데미지
    AttackDamage = 30.f;

    // 3단 콤보 평타용 콜리전 설정
    FSkillData Combo1Data;
    Combo1Data.DamageMultiplier = 1.0f;
    Combo1Data.AttackType = ESkillAttackType::RangedProjectile;
    Combo1Data.Range = FVector(100.f); // 의미 없음. 투사체 방식
    Combo1Data.Offset = FVector(100.f, 0.f, 0.f);
    Combo1Data.ProjectileClass = ArrowProjectileClass; // 던지는 액터

    SkillDataMap.Add("Combo1", Combo1Data);
    SkillDataMap.Add("Combo2", Combo1Data);
    SkillDataMap.Add("Combo3", Combo1Data);


    // 대쉬 스킬 데이터 초기화
    FSkillData DashSkillData;
    DashSkillData.DamageMultiplier = 2;
    DashSkillData.AttackType = ESkillAttackType::MeleeSphere;
    DashSkillData.Range = FVector(300.f); // 대시 범위: 반경 300
    DashSkillData.Offset = FVector(250.f, 0.f, 0.f); // 캐릭터 앞쪽
    SkillDataMap.Add(FName("DashSkill"), DashSkillData);

    // 스페셜 스킬 콜리전 설정
    FSkillData SpecialSkillData;
    SpecialSkillData.DamageMultiplier = 3.f;
    SpecialSkillData.AttackType = ESkillAttackType::MeleeSphere;
    SpecialSkillData.Range = FVector(300.f);  // 반지름 300짜리 구체
    SpecialSkillData.Offset = FVector(600.f, 0.f, 0.f);
    SkillDataMap.Add(FName("SpecialSkill"), SpecialSkillData);


    bIsInvincible = false;
}

void ASW_Myth::BeginPlay()
{
    Super::BeginPlay();
}



// 콤보 어택 ==================================================================================================================
void ASW_Myth::ComboAttack()
{
    Super::ComboAttack();
}

void ASW_Myth::SpawnComboArrow(bool bIsSpecialSkill)
{
    FVector CharacterLocation = GetActorLocation();
    FVector Direction;
    FVector SpawnLocation;

    bool bIsJumpSkill = bIsJumpAttacking;

    if (bIsSpecialSkill || bIsJumpSkill)
    {
        // 45도 아래 방향
        FVector Forward = GetActorForwardVector() * 0.7071f;
        FVector Downward = FVector::DownVector * 0.7071f;
        Direction = (Forward + Downward).GetSafeNormal();

        // 위치: 스페셜스킬은 위에서, 점프어택은 현재 위치 기준
        FVector Start = CharacterLocation;
        if (bIsSpecialSkill)
        {
            Start += FVector(0.f, 0.f, 390.f);
        }

        SpawnLocation = Start + Direction * 100.f;
    }
    else
    {
        Direction = GetActorForwardVector();
        SpawnLocation = CharacterLocation + Direction * 100.f;
    }

    FRotator ArrowRotation = Direction.Rotation();

    FActorSpawnParameters Params;
    Params.Owner = this;
    Params.Instigator = this;

    AActor* Projectile = GetWorld()->SpawnActor<AActor>(ArrowProjectileClass, SpawnLocation, ArrowRotation, Params);
    if (ASW_Arrow* SpawnedArrow = Cast<ASW_Arrow>(Projectile))
    {
        // 스페셜스킬 또는 점프어택일 때는 데미지 0
        if (bIsSpecialSkill || bIsJumpSkill)
        {
            SpawnedArrow->Damage = 0.f;
        }
        else
        {
            SpawnedArrow->Damage = AttackDamage;
        }

        if (UStaticMeshComponent* MeshComp = SpawnedArrow->FindComponentByClass<UStaticMeshComponent>())
        {
            switch (CurrentComboIndex)
            {
            case 0: MeshComp->SetMaterial(0, FirstMaterial); break;
            case 1: MeshComp->SetMaterial(0, SecondMaterial); break;
            case 2: MeshComp->SetMaterial(0, ThirdMaterial); break;
            }
        }

        SpawnedArrow->SetActorScale3D(FVector(1.f));
    }
}
// =============================================================================================================================




// 노멀스킬 ====================================================================================================================
void ASW_Myth::NormalSkill()
{
    if (!HasAuthority()) return;
    PlaySkillAnimation(FName("NormalSkill"));
}

AActor* ASW_Myth::SpawnArrow(bool bFanShape, bool bIsNormalSkill)
{
    FVector CharacterLocation = GetActorLocation();
    FVector CharacterForward = GetActorForwardVector();

    // 점프어택 중이면 → 정면X, 대각선 아래 방향으로 단일 발사
    TArray<float> ArrowAngles;
    if (bIsJumpAttacking)
    {
        ArrowAngles = { 0.f }; // 하나만 발사
    }
    else if (bFanShape)
    {
        ArrowAngles = { -10.f, 0.f, 10.f }; // 부채꼴
    }
    else
    {
        ArrowAngles = { 0.f }; // 정면 1발
    }

    AActor* LastProjectile = nullptr;

    for (float Angle : ArrowAngles)
    {
        FVector Direction;

        if (bIsJumpAttacking)
        {
            // 정면 + 아래 방향으로 45도 (x축 0.7071, z축 -0.7071)
            FVector Forward = CharacterForward * 0.7071f;
            FVector Downward = FVector::DownVector * 0.7071f;
            Direction = (Forward + Downward).GetSafeNormal();
        }
        else
        {
            // 기존 방식
            FRotator RotationOffset(0.f, Angle, 0.f);
            Direction = RotationOffset.RotateVector(CharacterForward);
        }

        FVector SpawnLocation = CharacterLocation + Direction * 100.f;
        FRotator ArrowRotation = Direction.Rotation();

        FActorSpawnParameters Params;
        Params.Owner = this;
        Params.Instigator = this;

        AActor* Projectile = GetWorld()->SpawnActor<AActor>(ArrowProjectileClass, SpawnLocation, ArrowRotation, Params);

        if (ASW_Arrow* SpawnedArrow = Cast<ASW_Arrow>(Projectile))
        {
            // 데미지 설정
            if (bIsJumpAttacking)
            {
                SpawnedArrow->Damage = 0.f;
            }
            else if (bIsNormalSkill)
            {
                SpawnedArrow->Damage = AttackDamage * 2;
            }
            else
            {
                SpawnedArrow->Damage = AttackDamage;
            }

            // 머티리얼 설정
            if (UStaticMeshComponent* MeshComp = SpawnedArrow->FindComponentByClass<UStaticMeshComponent>())
            {
                if (bIsNormalSkill && NormalSkillMaterial)
                {
                    MeshComp->SetMaterial(0, NormalSkillMaterial);
                }
            }

            // 화살 스케일
            SpawnedArrow->SetActorScale3D(FVector(1.f));

            // 1초 뒤 자동 파괴
            FTimerHandle TimerHandle;
            GetWorld()->GetTimerManager().SetTimer(
                TimerHandle,
                [Projectile]()
                {
                    if (IsValid(Projectile))
                    {
                        Projectile->Destroy();
                    }
                },
                1.0f,
                false
            );

            LastProjectile = Projectile;
        }
    }

    return LastProjectile;
}
// =============================================================================================================================


void ASW_Myth::DashSkill()
{
    // 후방 회피 애니메이션 실행
    PlaySkillAnimation(FName("DashSkill"));
}

void ASW_Myth::JumpAttack()
{
    if (!HasAuthority()) return;

    bIsJumpAttacking = true;

    // 0.5초 후 점프 어택 플래그 해제
    GetWorld()->GetTimerManager().SetTimer(JumpAttackFlagTimerHandle, [this]()
        {
            bIsJumpAttacking = false;
        }, 0.5f, false);

    LaunchCharacter(-GetActorForwardVector() * 1000.f, true, true);

    // 0.4초 뒤에 MythSpawnActor 생성
    FTimerHandle SpawnDelayTimer;
    GetWorld()->GetTimerManager().SetTimer(
        SpawnDelayTimer,
        [this]()
        {
            if (MythSpawnActorClass)
            {
                FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 400.f + FVector(0, 0, -70.f);
                FRotator SpawnRotation = GetActorRotation();

                FActorSpawnParameters Params;
                Params.Owner = this;
                Params.Instigator = this;

                AActor* Spawned = GetWorld()->SpawnActor<AActor>(MythSpawnActorClass, SpawnLocation, SpawnRotation, Params);
                if (ASW_MythSpawnActor* DamageZone = Cast<ASW_MythSpawnActor>(Spawned))
                {
                    DamageZone->OwnerCharacter = this;
                    DamageZone->Damage = AttackDamage;
                    DamageZone->DamageMultiplier = 3.f; // 데미지 기본어택데미지 곱하기 2
                    DamageZone->Range = FVector(300.f);
                    DamageZone->Offset = FVector(0.f, 0.f, 0.f);
                }
            }
        },
        0.2f, // 0.2초 뒤에 액터 생성 (화살이 지면에 닿는 시간용)
        false  
    );

    PlaySkillAnimation(FName("JumpAttack"));
}

void ASW_Myth::SpecialSkill()
{
    if (!HasAuthority()) return;

    bIsInvincible = true;

    // 3초 후 무적 해제
    FTimerHandle InvincibleTimerHandle;
    GetWorld()->GetTimerManager().SetTimer(
        InvincibleTimerHandle,
        [this]()
        {
            bIsInvincible = false;
        },
        3.0f,
        false
    );

    PlaySkillAnimation(FName("SpecialSkill"));
}

