#include "SW_Void.h"
#include "SW_Magic.h"  // SW_Magic: 마법 투사체 클래스 (SW_ThrowActor 기반)
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"

ASW_Void::ASW_Void()
{
    // 애니메이션 몽타주 초기화 (콤보 공격용)
    static ConstructorHelpers::FObjectFinder<UAnimMontage> Combo1(TEXT("/Game/Characters/Void/Animation/ComboAttack/AM_Void_Combo1.AM_Void_Combo1"));
    static ConstructorHelpers::FObjectFinder<UAnimMontage> Combo2(TEXT("/Game/Characters/Void/Animation/ComboAttack/AM_Void_Combo2.AM_Void_Combo2"));
    static ConstructorHelpers::FObjectFinder<UAnimMontage> Combo3(TEXT("/Game/Characters/Void/Animation/ComboAttack/AM_Void_Combo3.AM_Void_Combo3"));
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
}

void ASW_Void::BeginPlay()
{
    Super::BeginPlay();
}

void ASW_Void::ComboAttack()
{
    if (HasAuthority() && SpellProjectileClass)
    {
        FVector SpawnLocation = GetMesh()->GetSocketLocation("SpellSocket");
        FRotator SpawnRotation = GetControlRotation();

        // 3번의 투사체 발사
        for (int32 i = 0; i < 3; i++)
        {
            FActorSpawnParameters SpawnParams;
            SpawnParams.Owner = this;
            SpawnParams.Instigator = GetInstigator();
            AActor* Projectile = GetWorld()->SpawnActor<AActor>(SpellProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);
            if (Projectile)
            {
                // 3번째 투사체는 2배 크기로 생성
                if (i == 2)
                {
                    Projectile->SetActorScale3D(FVector(2.f));
                }
            }
        }
    }
    // ApplyCombo Notify사용으로 차후 수정 필요
    //PlaySkillAnimation(FName("BasicAttack"));
}

void ASW_Void::NormalSkill()
{
    if (HasAuthority() && SpellProjectileClass)
    {
        // 화살 생성 위치를 캐릭터의 소켓 위치로 설정
        FVector SpawnLocation = GetMesh()->GetSocketLocation("SpellSocket");

        // 컨트롤러의 방향을 기반으로 회전값 설정 (캐릭터가 보는 방향)
        FRotator SpawnRotation = Controller ? Controller->GetControlRotation() : GetActorRotation();

        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        SpawnParams.Instigator = GetInstigator();

        // 투사체 생성
        AActor* Projectile = GetWorld()->SpawnActor<AActor>(SpellProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);
        if (Projectile)
        {
            // 크기를 조정하거나 기타 설정 추가 가능
            Projectile->SetActorScale3D(FVector(3.f));
        }
    }

    // 스킬 애니메이션 재생
    PlaySkillAnimation(FName("NormalSkill"));
}

void ASW_Void::JumpAttack()
{
    if (HasAuthority())
    {
        // 이동 멈춤 및 방어막 획득 (방어막 로직은 별도 구현)
        GetCharacterMovement()->StopMovementImmediately();
        UE_LOG(LogTemp, Log, TEXT("Void DownAttack: Shield activated."));
    }
    PlaySkillAnimation(FName("JumpAttack"));
}

void ASW_Void::DashSkill()
{
    // 전방 600 단위 이동(텔레포트)
    FVector TeleportLocation = GetActorLocation() + GetActorForwardVector() * 600.f;
    TeleportLocation.Z = GetActorLocation().Z;
    TeleportTo(TeleportLocation, GetActorRotation());
    PlaySkillAnimation(FName("DashSkill"));
}


void ASW_Void::UltimateSkill()
{
    if (HasAuthority() && SpellProjectileClass)
    {
        FVector SpawnLocation = GetMesh()->GetSocketLocation("SpellSocket");
        FRotator SpawnRotation = GetControlRotation();
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        SpawnParams.Instigator = GetInstigator();
        // 예시: 단일 강력한 투사체 발사 (추가 효과는 필요에 따라 구현)
        GetWorld()->SpawnActor<AActor>(SpellProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);
    }
    PlaySkillAnimation(FName("SpecialSkill"));
}
