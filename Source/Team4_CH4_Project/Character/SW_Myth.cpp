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
    DashSkillData.DamageMultiplier = 1.5;
    DashSkillData.AttackType = ESkillAttackType::MeleeSphere;
    DashSkillData.Range = FVector(300.f); // 대시 범위: 반경 300
    DashSkillData.Offset = FVector(250.f, 0.f, 0.f); // 캐릭터 앞쪽
    SkillDataMap.Add(FName("DashSkill"), DashSkillData);

    // 스페셜 스킬 콜리전 설정
    FSkillData SpecialSkillData;
    SpecialSkillData.DamageMultiplier = 8.f; // 데미지 계수 8배
    SpecialSkillData.AttackType = ESkillAttackType::MeleeBox;
    SpecialSkillData.Range = FVector(300.f, 300.f, 200.f);
    SpecialSkillData.Offset = FVector(500.f, 0.f, 0.f); // 정면 500 위치
    SkillDataMap.Add(FName("SpecialSkill"), SpecialSkillData);


    bIsInvincible = false;
}

void ASW_Myth::BeginPlay()
{
    Super::BeginPlay();
}

AActor* ASW_Myth::SpawnArrow()
{
    FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 100.f;
    FVector TargetLocation;

    if (bIsJumpAttacking)
    {
        // 점프 어택일 때는 MythSpawnActor 생성 위치로 화살 발사 (데미지 0)
        TargetLocation = GetActorLocation() + GetActorForwardVector() * 250.f + FVector(0, 0, -100.f);
    }
    else
    {
        TargetLocation = SpawnLocation + GetActorForwardVector() * 1000.f; // 바라보는 뒤쪽 방향으로 1000만큼 이동
    }

    FVector Direction = (TargetLocation - SpawnLocation).GetSafeNormal();
    FRotator SpawnRotation = Direction.Rotation();

    FActorSpawnParameters Params;
    Params.Owner = this;
    Params.Instigator = this;

    AActor* Projectile = GetWorld()->SpawnActor<AActor>(ArrowProjectileClass, SpawnLocation, SpawnRotation, Params);
    if (Projectile)
    {
        Projectile->SetActorScale3D(FVector(1.f));

        if (ASW_Arrow* Arrow = Cast<ASW_Arrow>(Projectile))
        {
            Arrow->SpawnActorClass = MythSpawnActorClass;
            Arrow->OwnerCharacter = this;
        }

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
    }

    return Projectile;
}

void ASW_Myth::SpawnComboArrow()
{
    AActor* Projectile = SpawnArrow();
    if (Projectile)
    {
        if (ASW_Arrow* SpawnedArrow = Cast<ASW_Arrow>(Projectile))
        {
            // 점프 어택 또는 궁극기 시 데미지 0
            if (bIsJumpAttacking)
            {
                SpawnedArrow->Damage = 0.f;
            }
            else
            {
                float baseDamage = 20.f;
                float comboAddedDamage = CurrentComboIndex * 20.f;
                SpawnedArrow->Damage = baseDamage + comboAddedDamage;
            }

            // 머티리얼 설정 (기존 코드 유지)
            UStaticMeshComponent* MeshComp = SpawnedArrow->FindComponentByClass<UStaticMeshComponent>();
            if (MeshComp)
            {
                switch (CurrentComboIndex)
                {
                case 0: MeshComp->SetMaterial(0, FirstMaterial); break;
                case 1: MeshComp->SetMaterial(0, SecondMaterial); break;
                case 2: MeshComp->SetMaterial(0, ThirdMaterial); break;
                }
            }
        }
    }
}

void ASW_Myth::ComboAttack()
{
    Super::ComboAttack();
}

void ASW_Myth::NormalSkill()
{
    // 서버 권한 체크
    if (!HasAuthority())
    {
        return;
    }

    // 캐릭터의 현재 전방 방향 벡터 (로컬 기준)
    FVector CharacterForward = GetActorForwardVector();
    // 캐릭터의 현재 위치
    FVector CharacterLocation = GetActorLocation();

    // 부채꼴 각도 설정 (예: -10도, 0도, +10도)
    TArray<float> ArrowAngles = { -10.f, 0.f, 10.f };

    // 각 각도에 따라 화살 생성
    for (float Angle : ArrowAngles)
    {
        // 1. 캐릭터 전방 방향을 기준으로 회전 적용
        FRotator RotationOffset(0.f, Angle, 0.f); // Yaw만 회전
        FVector Direction = RotationOffset.RotateVector(CharacterForward);

        // 2. 화살 스폰 위치: 캐릭터 위치 + 전방 방향 * 100 단위 거리
        FVector SpawnLocation = CharacterLocation + Direction * 100.f;

        // 3. 화살 발사 방향 설정 (캐릭터가 바라보는 방향 + 각도 적용)
        FRotator ArrowRotation = Direction.Rotation();

        // 화살 스폰
        FActorSpawnParameters Params;
        Params.Owner = this;
        Params.Instigator = this;
        AActor* Projectile = GetWorld()->SpawnActor<AActor>(ArrowProjectileClass, SpawnLocation, ArrowRotation, Params);

        if (Projectile)
        {
            // 머티리얼 적용 (기존 로직 유지)
            if (UStaticMeshComponent* MeshComp = Projectile->FindComponentByClass<UStaticMeshComponent>())
            {
                if (NormalSkillMaterial)
                {
                    MeshComp->SetMaterial(0, NormalSkillMaterial);
                }
            }

            Projectile->SetActorScale3D(FVector(1.f));

            // 1초 후 화살 제거
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
        }
    }

    // 애니메이션 재생
    PlaySkillAnimation(FName("NormalSkill"));
}

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
                    DamageZone->DamageMultiplier = 2.f; // 데미지 기본어택데미지 곱하기 2
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

    // 애니메이션 실행
    PlaySkillAnimation(FName("SpecialSkill"));

    // 2초 후 데미지 판정
    FTimerHandle DamageTimer;
    GetWorld()->GetTimerManager().SetTimer(
        DamageTimer,
        [this]()
        {
            Server_ApplySkillDamage(FName("SpecialSkill"));
        },
        1.7f,
        false
    );
}

