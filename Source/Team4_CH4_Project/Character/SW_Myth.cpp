#include "SW_Myth.h"
#include "SW_Arrow.h" 
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"

ASW_Myth::ASW_Myth()
{
    // 애니메이션 몽타주 초기화 (콤보 공격용)
    static ConstructorHelpers::FObjectFinder<UAnimMontage> Combo1(TEXT("/Game/Characters/Myth/Animation/ComboAttack/AM_Myth_Combo1.AM_Myth_Combo1"));
    static ConstructorHelpers::FObjectFinder<UAnimMontage> Combo2(TEXT("/Game/Characters/Myth/Animation/ComboAttack/AM_Myth_Combo2.AM_Myth_Combo2"));
    static ConstructorHelpers::FObjectFinder<UAnimMontage> Combo3(TEXT("/Game/Characters/Myth/Animation/ComboAttack/AM_Myth_Combo3.AM_Myth_Combo3"));
    
    if (Combo1.Succeeded()) ComboMontages.Add(Combo1.Object);
    if (Combo2.Succeeded()) ComboMontages.Add(Combo2.Object);
    if (Combo3.Succeeded()) ComboMontages.Add(Combo3.Object);

    // 스탯 초기화
    MaxHealth = 80;
    Health = MaxHealth;
    AttackDamage = 30.f;

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
    if (!HasAuthority() || !ArrowProjectileClass)
    {
        return nullptr;
    }

    FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 100.f;
    FRotator SpawnRotation = GetActorRotation();

    FActorSpawnParameters Params;
    Params.Owner = this;
    Params.Instigator = this;

    // 화살 생성
    AActor* Projectile = GetWorld()->SpawnActor<AActor>(ArrowProjectileClass, SpawnLocation, SpawnRotation, Params);
    if (Projectile)
    {
        Projectile->SetActorScale3D(FVector(1.f));

        FTimerHandle TimerHandle;
        GetWorld()->GetTimerManager().SetTimer(
            TimerHandle,
            [Projectile]()
            {
                if (IsValid(Projectile)) // IsValid로 화살이 유효한지 확인
                {
                    Projectile->Destroy();
                }
            },
            1.0f, // 지속 시간 (초)
            false // 반복 여부
        );
    }

    return Projectile;
}



void ASW_Myth::SpawnComboArrow()
{
    UE_LOG(LogTemp, Warning, TEXT("SpawnComboArrow called with ComboIndex: %d"), CurrentComboIndex);

    AActor* Projectile = SpawnArrow();
    if (Projectile)
    {
        if (ASW_Arrow* SpawnedArrow = Cast<ASW_Arrow>(Projectile))
        {
            float baseDamage = 20.f;
            float comboAddedDamage = CurrentComboIndex * 20.f;
            SpawnedArrow->Damage = baseDamage + comboAddedDamage;

            UE_LOG(LogTemp, Warning, TEXT("Arrow Damage set to: %f"), SpawnedArrow->Damage);

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
    UE_LOG(LogTemp, Warning, TEXT("BasicAttack started"));

    Super::ComboAttack();
}

void ASW_Myth::NormalSkill()
{
    // 서버 권한 체크
    if (!HasAuthority())
    {
        return;
    }

    // 캐릭터의 기본 회전 값
    FRotator BaseRotation = GetActorRotation();

    // 부채꼴 각도를 설정 (예: -10도, 0도, +10도)
    TArray<float> ArrowAngles = {-10.f, 0.f, 10.f};

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

void ASW_Myth::DashAttack()
{
    UE_LOG(LogTemp, Warning, TEXT("DashAttack 함수 호출됨"));

    if (!HasAuthority())
    {
        UE_LOG(LogTemp, Warning, TEXT("DashAttack: HasAuthority() false, 실행 중단"));
        return;
    }
    
    if (ArrowProjectileClass)
    {
        FVector SpawnLocation = GetMesh()->GetSocketLocation(TEXT("ArrowSocket"));
        FRotator SpawnRotation = GetControlRotation();
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        SpawnParams.Instigator = GetInstigator();
        
        AActor* SpawnedArrow = GetWorld()->SpawnActor<AActor>(ArrowProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);
        if (SpawnedArrow)
        {
            UE_LOG(LogTemp, Warning, TEXT("DashAttack: 화살 생성 성공"));
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("DashAttack: 화살 생성 실패"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("DashAttack: ArrowProjectileClass가 설정되어 있지 않음"));
    }
    
    GetWorldTimerManager().SetTimer(
        DashTimerHandle,
        this,
        &ASW_Myth::ExecuteDash,
        0.3f,
        false
    );
}

void ASW_Myth::ExecuteDash()
{
    // 후방 회피(백덤블링) 동작 실행
    FVector Backward = -GetActorForwardVector();
    float EvadeSpeed = 600.f;
    LaunchCharacter(Backward * EvadeSpeed, true, true);
    
    UE_LOG(LogTemp, Warning, TEXT("DashAttack: 후방 회피 실행, EvadeSpeed: %f"), EvadeSpeed);
    
    // 후방 회피 애니메이션 실행
    PlaySkillAnimation(FName("DashAttack"));
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
    PlaySkillAnimation(FName("UltimateSkill"));
}

void ASW_Myth::DownAttack()
{
    if (HasAuthority())
    {
        // 다운 어택: 단순히 보는 방향의 반대쪽으로 이동 (뒤로 백덤블링)
        FVector DownDirection = -GetActorForwardVector();
        float DownSpeed = 1000.f;
        LaunchCharacter(DownDirection * DownSpeed, true, true);
        PlaySkillAnimation(FName("DownAttack"));
    }
}
