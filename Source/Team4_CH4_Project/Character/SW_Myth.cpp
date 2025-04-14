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
        // 점프어택일 때는 MythSpawnActor가 생성될 위치로 화살발사
        TargetLocation = GetActorLocation() + GetActorForwardVector() * 250.f + FVector(0, 0, -60.f);
    }
    else
    {
        TargetLocation = SpawnLocation + GetActorForwardVector() * 1000.f; // 그냥 전방으로
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
            float baseDamage = 20.f;
            float comboAddedDamage = CurrentComboIndex * 20.f;
            SpawnedArrow->Damage = baseDamage + comboAddedDamage;

            UStaticMeshComponent* MeshComp = SpawnedArrow->FindComponentByClass<UStaticMeshComponent>();
            if (MeshComp)
            {
                switch (CurrentComboIndex)
                {
                case 0:
                    MeshComp->SetMaterial(0, FirstMaterial); // 첫 번째 머티리얼
                    break;
                case 1:
                    MeshComp->SetMaterial(0, SecondMaterial); // 두 번째 머티리얼
                    break;
                case 2:
                    MeshComp->SetMaterial(0, ThirdMaterial); // 세 번째 머티리얼
                    break;
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

    // 조준 방향 기준으로 회전 설정
    FRotator BaseRotation = GetControlRotation();

    // 부채꼴 각도를 설정 (예: -10도, 0도, +10도)
    TArray<float> ArrowAngles = { -10.f, 0.f, 10.f };

    // 각 각도에 따라 화살 생성
    for (float Angle : ArrowAngles)
    {
        // 현재 화살 회전 각도 계산 (BaseRotation에 Yaw 값을 더하거나 뺌)
        FRotator ArrowRotation = BaseRotation;
        ArrowRotation.Yaw += Angle;

        // 화살 스폰 위치: 캐릭터 전방으로 100 단위 거리
        FVector SpawnLocation = GetActorLocation() + ArrowRotation.Vector() * 100.f;

        // 화살 스폰
        FActorSpawnParameters Params;
        Params.Owner = this;
        Params.Instigator = this;
        AActor* Projectile = GetWorld()->SpawnActor<AActor>(ArrowProjectileClass, SpawnLocation, ArrowRotation, Params);

        if (Projectile)
        {
            // StaticMeshComponent를 찾아 머티리얼 적용
            if (UStaticMeshComponent* MeshComp = Projectile->FindComponentByClass<UStaticMeshComponent>())
            {
                if (NormalSkillMaterial) // NormalSkillMaterial이 설정되어 있다면 적용
                {
                    MeshComp->SetMaterial(0, NormalSkillMaterial);
                }
            }

            // 필요 시 크기 조정
            Projectile->SetActorScale3D(FVector(1.f));

            // 1초 후에 화살 제거 (Destroy)
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
                1.0f,      // 1초 후 실행
                false      // 반복 실행 아님
            );
        }
    }

    // 기본 스킬 애니메이션 재생
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

    GetWorld()->GetTimerManager().SetTimer(JumpAttackFlagTimerHandle, [this]()
        {
            bIsJumpAttacking = false;
        }, 0.5f, false);

    LaunchCharacter(-GetActorForwardVector() * 1000.f, true, true);

    if (MythSpawnActorClass)
    {
        FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 400.f + FVector(0, 0, -70.f);
        FRotator SpawnRotation = GetActorRotation(); // 회전값을 캐릭터 방향과 일치시킴

        FActorSpawnParameters Params;
        Params.Owner = this;
        Params.Instigator = this;

        AActor* Spawned = GetWorld()->SpawnActor<AActor>(MythSpawnActorClass, SpawnLocation, SpawnRotation, Params);
        if (ASW_MythSpawnActor* DamageZone = Cast<ASW_MythSpawnActor>(Spawned))
        {
            DamageZone->OwnerCharacter = this;
            DamageZone->Damage = AttackDamage;
            DamageZone->DamageMultiplier = 2.f;        // 2배 데미지
            DamageZone->Range = FVector(300.f);        // 스킬 충돌 반경
            DamageZone->Offset = FVector(0.f, 0.f, 0.f); // 필요시 위치 오프셋
        }
    }

    PlaySkillAnimation(FName("JumpAttack"));
}

void ASW_Myth::UltimateSkill()
{
    if (HasAuthority())
    {
        bIsInvincible = true;
        // 3초 후 무적 해제
        FTimerHandle InvincibleTimer;
        GetWorldTimerManager().SetTimer(InvincibleTimer, [this]()
            {
                bIsInvincible = false;
            }, 3.f, false);

        // 궁극: 좁은 범위로 화살 3발 발사
        if (ArrowProjectileClass)
        {
            FVector SpawnLocation = GetMesh()->GetSocketLocation("ArrowSocket");
            FRotator BaseRotation = GetControlRotation();
            for (int32 Offset = -1; Offset <= 1; Offset++)
            {
                FRotator SpawnRotation = BaseRotation;
                SpawnRotation.Yaw += Offset * 5.f;
                FActorSpawnParameters SpawnParams;
                SpawnParams.Owner = this;
                SpawnParams.Instigator = GetInstigator();
                GetWorld()->SpawnActor<AActor>(ArrowProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);
            }
        }
    }
    PlaySkillAnimation(FName("SpecialSkill"));
}

