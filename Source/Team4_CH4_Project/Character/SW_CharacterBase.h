#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Components/WidgetComponent.h"
#include "SW_HP.h"
#include "GameFramework/DamageType.h"
#include "SW_CharacterBase.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UAnimMontage;

// 스킬 데미지 관련 =================================================================
UENUM(BlueprintType)
enum class ESkillAttackType : uint8
{
    MeleeSphere,    // 근접 스피어 오버랩
    MeleeBox,       // 근접 박스 오버랩
    BoxTrace,
    RangedTrace,    // 원거리 라인 트레이스
    RangedProjectile // 원거리 투사체
};

USTRUCT(BlueprintType)
struct FSkillData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
    float DamageMultiplier = 1.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
    ESkillAttackType AttackType = ESkillAttackType::MeleeSphere;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
    FVector Range = FVector(200.f);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
    FVector Offset = FVector::ZeroVector;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
    TSubclassOf<AActor> ProjectileClass;
};
// =============================================================================

UCLASS()
class TEAM4_CH4_PROJECT_API ASW_CharacterBase : public ACharacter
{
    GENERATED_BODY()

public:
    ASW_CharacterBase();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    virtual void Player_Move(const FInputActionValue& _InputValue);
    virtual void Player_Jump(const FInputActionValue& _InputValue);
    virtual void ComboAttack();
    virtual void JumpAttack();
    virtual void NormalSkill();
    virtual void SpecialSkill();
    virtual void DashSkill();

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    USpringArmComponent* CameraBoom;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    UCameraComponent* FollowCamera;

    // 체력바
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
    UWidgetComponent* HealthBarWidget;

    // 기본 데미지
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
    float AttackDamage = 50.f;

    // ================TakeDmage()함수용================
    // 피격 애니메이션
    UPROPERTY(EditAnywhere, Category = "Animation")
    UAnimMontage* HitReactionMontage;
    // 사망 애니메이션
    UPROPERTY(EditAnywhere, Category = "Animation")
    UAnimMontage* DeathMontage;
    //===================================================



    // ===================== 콤보 시스템용 ==============================
    UPROPERTY(EditDefaultsOnly, Category = "Combo")
    TArray<UAnimMontage*> ComboMontages;

    UPROPERTY(VisibleAnywhere, Category = "Combo")
    int32 CurrentComboIndex = 0;

    UPROPERTY(VisibleAnywhere, Category = "Combo")
    bool bCanNextCombo = true;

    UPROPERTY(VisibleAnywhere, Category = "Combo")
    bool bPendingNextCombo = false;

    // 점프중에 공격가능한지 확인하는 변수
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
    bool bIsJumpAttacking;

    // 공격중인지 확인하는 변수
    UPROPERTY(Replicated)
    bool bIsAttacking;

    // 이동만 멈추는 상태 (입력은 가능)
    UPROPERTY(Replicated)
    bool bIsMovementLocked;
    // ====================================================================

    // === 스킬 애니메이션 관리 ===
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
    TMap<FName, UAnimMontage*> SkillMontages;

    // 애니메이션 재생 중 입력 차단 상태
    UPROPERTY(Replicated)
    bool bIsLocked;

protected:

    // 스킬 데이터 (기본값은 자식 클래스에서 설정)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
    TMap<FName, FSkillData> SkillDataMap;

    // 캐릭터 이동속도 변수
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float DefaultMoveSpeed = 600.f;

    UPROPERTY(VisibleAnywhere, Category = "Movement")
    FVector Acceleration;

    UPROPERTY(VisibleAnywhere, Category = "Movement")
    FVector Velocity;

    UPROPERTY(VisibleAnywhere, Category = "Movement")
    FVector AccelerationLastFrame;

    UPROPERTY(VisibleAnywhere, Category = "Movement")
    FVector VelocityLastFrame;



    // =======================캐릭터 체력 ============================
    UPROPERTY(EditDefaultsOnly, Category = "Stat")
    int32 MaxHealth;

    // 체력 리플리케이션
    UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_Health, Category = "Stat")
    int32 Health;

    UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_Death, Category = "Stat")
    bool bDead;

    UFUNCTION()
    void OnRep_Health();

    UFUNCTION()
    void OnRep_Death();

    UFUNCTION()
    void Character_Die();
    // ==============================================================



public:

    // 콤보 평타 리셋용
    void ResetCombo();

    // 콤보 평타용으로 콤보 인풋액션 입력시 CurrentIndex증가용 함수
    void CheckPendingCombo();

    // 스킬시전중에 다른 입력 못하는 함수
    UFUNCTION(BlueprintCallable)
    void SetLockedState(bool bLocked);

    // 멈추거나 다시 움직일 수있게 해주는 함수
    UFUNCTION(BlueprintCallable)
    void SetMovementLocked(bool bLocked);

    // 캐릭터 체력바 함수
    UFUNCTION(BlueprintCallable)
    void UpdateHealthBar();

    // 데미지 처리
    UFUNCTION(BlueprintCallable, Category = "Stat")
    virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

    // 타격 범위 내 대상 탐지 (가상 함수로 자식 클래스에서 커스터마이징 가능)
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Skill")
    TArray<AActor*> GetTargetsInRange(FName SkillName);
    virtual TArray<AActor*> GetTargetsInRange_Implementation(FName SkillName);

    // 데미지 적용 (공통 로직)
    UFUNCTION(BlueprintCallable, Category = "Skill")
    void ApplySkillDamage(FName SkillName, const TArray<AActor*>& Targets);

    // =========================== 리플리케이션용 함수 ==============================

    // 스킬애니메이션 모음집 함수
    UFUNCTION(BlueprintCallable)
    void PlaySkillAnimation(FName SkillName);


    UFUNCTION(Server, Reliable)
    void Server_PlaySkill(FName SkillName);

    UFUNCTION(NetMulticast, Reliable)
    void Multicast_PlaySkill(FName SkillName);



    UFUNCTION(Server, Reliable)
    void Server_ApplySkillDamage(FName SkillName);

    UFUNCTION(NetMulticast, Reliable)
    void Multicast_ApplySkillDamage(FName SkillName);

    UFUNCTION(NetMulticast, Reliable)
    void Multicast_ComboAttack();

};