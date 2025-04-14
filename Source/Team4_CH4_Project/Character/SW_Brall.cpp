#include "SW_Brall.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DamageEvents.h"
#include "InputActionValue.h"

ASW_Brall::ASW_Brall()
    : ASW_CharacterPlayer()
{
    // 리플리케이션 용
    bReplicates = true;
    SetReplicateMovement(true);

    // 체력
    MaxHealth = 500;
    Health = MaxHealth;

    // 기본 데미지
    AttackDamage = 40;


    // 대시 충돌 용 몸 전체 박스 콜리전 생성
    DashCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("DashCollider"));
    DashCollider->SetupAttachment(RootComponent);
    DashCollider->SetBoxExtent(FVector(150.f, 100.f, 100.f)); // X: 앞뒤, Y: 좌우, Z: 높이
    DashCollider->SetRelativeLocation(FVector(120.f, 0.f, 0.f)); // 앞쪽으로 밀기
    DashCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    DashCollider->SetCollisionResponseToAllChannels(ECR_Ignore);
    DashCollider->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
    DashCollider->OnComponentBeginOverlap.AddDynamic(this, &ASW_Brall::OnDashBoxOverlap);
    DashCollider->SetHiddenInGame(false); // 디버그용
    DashCollider->SetVisibility(true); // 디버그용

    // 2단 점프용 애니메이션 몽타주 주소
    static ConstructorHelpers::FObjectFinder<UAnimMontage> JumpStartMontage(TEXT("/Game/Characters/Brall/Animation/Jump/AM_Brall_2StepJump.AM_Brall_2StepJump"));
    if (JumpStartMontage.Succeeded())
    {
        SkillMontages.Add(FName("Brall_JumpAttackStart"), JumpStartMontage.Object);
    }

    static ConstructorHelpers::FObjectFinder<UAnimMontage> Combo1(TEXT("/Game/Characters/Brall/Animation/ComboAttack/AM_Brall_Combo1.AM_Brall_Combo1"));
    static ConstructorHelpers::FObjectFinder<UAnimMontage> Combo2(TEXT("/Game/Characters/Brall/Animation/ComboAttack/AM_Brall_Combo2.AM_Brall_Combo2"));
    static ConstructorHelpers::FObjectFinder<UAnimMontage> Combo3(TEXT("/Game/Characters/Brall/Animation/ComboAttack/AM_Brall_Combo3.AM_Brall_Combo3"));

    if (Combo1.Succeeded()) ComboMontages.Add(Combo1.Object);
    if (Combo2.Succeeded()) ComboMontages.Add(Combo2.Object);
    if (Combo3.Succeeded()) ComboMontages.Add(Combo3.Object);

    // 기본 스킬 설정
    FSkillData NormalSkillData;
    NormalSkillData.DamageMultiplier = 1.5f; // 데미지 계수
    NormalSkillData.AttackType = ESkillAttackType::BoxTrace;
    NormalSkillData.Range = FVector(600.f, 200.f, 300.f); // X: 길이, Y: 폭, Z: 높이
    NormalSkillData.Offset = FVector(300.f, 0.f, 0.f);
    SkillDataMap.Add(FName("NormalSkill"), NormalSkillData);

    // 스페셜 스킬 설정
    FSkillData SpecialSkillData;
    SpecialSkillData.DamageMultiplier = 1.5f; // 데미지 계수
    SpecialSkillData.AttackType = ESkillAttackType::MeleeBox; // Box
    SpecialSkillData.Range = FVector(300.f, 300.f, 200.f);  
    SpecialSkillData.Offset = FVector(200.f, 0.f, 0.f);        // 살짝 앞쪽으로
    SkillDataMap.Add(FName("SpecialSkill"), SpecialSkillData);

    // 점프 공격
    FSkillData JumpAttackData;
    JumpAttackData.DamageMultiplier = 1.5f; // 데미지 계수
    JumpAttackData.AttackType = ESkillAttackType::MeleeBox;
    JumpAttackData.Range = FVector(200.f, 200.f, 200.f); // 범위 설정
    JumpAttackData.Offset = FVector(200.f, 0.f, -50.f);    // 착지 지점 아래쪽
    SkillDataMap.Add(FName("JumpAttack"), JumpAttackData);
}

void ASW_Brall::BeginPlay()
{
    Super::BeginPlay();

    TArray<UChildActorComponent*> ChildActorComps;
    GetComponents<UChildActorComponent>(ChildActorComps);

    for (auto* Comp : ChildActorComps)
    {
        if (Comp && Comp->GetName().Contains("BrallSword"))
        {
            Sword = Comp;
            break;
        }
    }

    if (!Sword)
    {
        return;
    }

    if (!Sword->GetChildActor())
    {
        return;
    }

    SwordCollider = Sword->GetChildActor()->FindComponentByClass<UBoxComponent>();
    if (!SwordCollider)
    {
        return;
    }


    SwordCollider->OnComponentBeginOverlap.AddDynamic(this, &ASW_Brall::OnSwordOverlap);
    SwordCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    SwordCollider->SetHiddenInGame(false);
    SwordCollider->SetVisibility(true);
}

// 평타 콤보용 ==============================================================================
void ASW_Brall::OnSwordOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor != this && !AlreadyHitActors.Contains(OtherActor))
    {
        int32 Damage = FMath::RoundToInt(AttackDamage * 1.f);
        if (CurrentComboIndex == 2) // 1타
        {
            Damage = AttackDamage  * 1 + 10;
        }

        FDamageEvent DamageEvent;
        OtherActor->TakeDamage(Damage, DamageEvent, GetController(), this);
        AlreadyHitActors.Add(OtherActor);
    }
}

void ASW_Brall::SwordAttackStart()
{
    AlreadyHitActors.Empty();

    if (SwordCollider)  // null 체크 추가
    {
        SwordCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    }
}

void ASW_Brall::SwordAttackEnd()
{
    if (SwordCollider)  // null 체크 추가
    {
        SwordCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    }
}
// ===========================================================================================



// 대쉬 스킬용 ================================================================================
void ASW_Brall::DashSkill()
{
    Super::DashSkill();

    GetWorldTimerManager().SetTimer(
        DashTimerHandle,
        this,
        &ASW_Brall::ExecuteDesh,
        0.3f,
        false
    );
}

void ASW_Brall::ExecuteDesh()
{
    FVector DashDirection = GetActorForwardVector().GetSafeNormal();
    float DashSpeed = 2000.f;

    AlreadyHitActors.Empty();
    DashCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly); // 박스 ON

    UCharacterMovementComponent* MoveComp = GetCharacterMovement();
    MoveComp->BrakingFrictionFactor = 0.f;
    MoveComp->BrakingDecelerationWalking = 0.f;

    LaunchCharacter(DashDirection * DashSpeed, true, true);

    FTimerHandle DashResetHandle;
    GetWorldTimerManager().SetTimer(DashResetHandle, FTimerDelegate::CreateLambda([this, MoveComp]()
        {
            MoveComp->BrakingFrictionFactor = 2.f;
            MoveComp->BrakingDecelerationWalking = 2048.f;
            DashCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision); // 박스 off
        }), 0.5f, false);
}

void ASW_Brall::OnDashBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor != this && !AlreadyHitActors.Contains(OtherActor))
    {
        int32 Damage = FMath::RoundToInt(AttackDamage * 1.5f);

        FDamageEvent DamageEvent;
        OtherActor->TakeDamage(Damage, DamageEvent, GetController(), this);
        AlreadyHitActors.Add(OtherActor);
    }
}
// ==============================================================================================


// 점프 공격용 ================================================================================
void ASW_Brall::JumpAttack()
{
    if (!GetCharacterMovement()->IsFalling()) return;
    if (bIsLocked) return;

    bIsJumpAttacking = true;

    // 45도 방향으로 점프
    FVector Forward = GetActorForwardVector() * 0.707f;
    FVector Up = FVector::UpVector * 0.707f;
    FVector JumpDir = (Forward + Up).GetSafeNormal();

    // 중력 OFF + 점프 시작
    UCharacterMovementComponent* MoveComp = GetCharacterMovement();
    MoveComp->GravityScale = 0.f;
    LaunchCharacter(JumpDir * 1000.f, true, true);

    // 점프 애니메이션 재생
    PlaySkillAnimation(FName("Brall_JumpAttackStart"));

    // 0.3초 후 25도 각도로 낙하
    FTimerHandle DiveTimer;
    GetWorldTimerManager().SetTimer(DiveTimer, FTimerDelegate::CreateLambda([this]()
        {
            UCharacterMovementComponent* MoveComp = GetCharacterMovement();

            MoveComp->StopMovementImmediately(); // 멈춤
            MoveComp->GravityScale = 1.f;        // 중력 ON

            // 25도 낙하 방향
            FVector Forward = GetActorForwardVector() * 0.9063f;
            FVector Down = FVector::DownVector * 0.4226f;
            FVector DiveDir = (Forward + Down).GetSafeNormal();

            // 낙하 속도
            LaunchCharacter(DiveDir * 1000.f, true, true);

            // 낙하 시 애니메이션 재생
            PlaySkillAnimation(FName("JumpAttack"));

        }), 0.3f, false);
}
// =============================================================================================


