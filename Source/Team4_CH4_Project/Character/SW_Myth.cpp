#include "SW_Myth.h"
#include "SW_Arrow.h"  // SW_Arrow: 화살 투사체 클래스 (SW_ThrowActor 기반)
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

    // 화살 스폰 위치 및 방향 설정 (캐릭터 앞쪽 100 단위)
    FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 100.f;
    FRotator SpawnRotation = GetActorRotation();

    FActorSpawnParameters Params;
    Params.Owner = this;
    Params.Instigator = this;

    AActor* Projectile = GetWorld()->SpawnActor<AActor>(ArrowProjectileClass, SpawnLocation, SpawnRotation, Params);
    if (Projectile)
    {
        Projectile->SetActorScale3D(FVector(1.f));  // 옵션: 크기 조정
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

            // 화살의 외형 변경 로직 추가
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
                default:
                    MeshComp->SetMaterial(0, DefaultMaterial); // 기본 머티리얼
                    break;
                }
            }
        }
    }
}






void ASW_Myth::ComboAttack()
{
    UE_LOG(LogTemp, Warning, TEXT("BasicAttack started"));

    // 부모 콤보 로직 호출
    Super::ComboAttack();
}

void ASW_Myth::NormalSkill()
{
    // 서버 권한 체크
    if (!HasAuthority())
    {
        return;
    }
    SpawnArrow();

    // 기본 스킬 애니메이션 재생
    PlaySkillAnimation(FName("NormalSkill"));
}
void ASW_Myth::DashAttack()
{
    if (HasAuthority())
    {
        // 전방으로 화살 발사
        if (ArrowProjectileClass)
        {
            FVector SpawnLocation = GetMesh()->GetSocketLocation("ArrowSocket");
            FRotator SpawnRotation = GetControlRotation();
            FActorSpawnParameters SpawnParams;
            SpawnParams.Owner = this;
            SpawnParams.Instigator = GetInstigator();
            GetWorld()->SpawnActor<AActor>(ArrowProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);
        }
        // 전방 대시
        FVector DashDirection = GetActorForwardVector().GetSafeNormal();
        float DashSpeed = 2000.f;
        LaunchCharacter(DashDirection * DashSpeed, true, true);
        // 0.2초 후 후방 회피(백덤블링) 실행
        FTimerHandle BackTumbleTimer;
        GetWorldTimerManager().SetTimer(BackTumbleTimer, [this]()
        {
            FVector Backward = -GetActorForwardVector();
            float EvadeSpeed = 600.f;
            LaunchCharacter(Backward * EvadeSpeed, true, true);
            PlaySkillAnimation(FName("DashAttack"));
        }, 0.2f, false);
    }
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
