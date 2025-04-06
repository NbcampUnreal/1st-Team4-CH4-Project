#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "SW_CharacterBase.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UAnimMontage;

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
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

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

    // === 콤보 시스템용 ===
    UPROPERTY(EditDefaultsOnly, Category = "Combo")
    TArray<UAnimMontage*> ComboMontages;

    UPROPERTY(VisibleAnywhere, Category = "Combo")
    int32 CurrentComboIndex = 0;

    UPROPERTY(VisibleAnywhere, Category = "Combo")
    bool bCanNextCombo = true;

    UPROPERTY(VisibleAnywhere, Category = "Combo")
    bool bPendingNextCombo = false;

    // === 스킬 애니메이션 관리 ===
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
    TMap<FName, UAnimMontage*> SkillMontages;

    // 애니메이션 재생 중 입력 차단 상태
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
    bool bIsLocked = false;

protected:
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
    
    // 아직은 미사용 중 
    UPROPERTY(VisibleAnywhere, Replicated, Category = "Stat")
    int32 Health;

    // 아직은 미사용 중 
    UPROPERTY(VisibleAnywhere, Replicated, Category = "Stat")
    int32 Stamina;

public:

    // 콤보 평타 리셋용
    void ResetCombo();

    // 콤보 평타용으로 콤보 인풋액션 입력시 CurrentIndex증가용 함수
    void CheckPendingCombo();

    // 스킬애니메이션 모음집 함수
    UFUNCTION(BlueprintCallable)
    void PlaySkillAnimation(FName SkillName);

    // 스킬시전중에 다른 입력 못하는 함수
    UFUNCTION(BlueprintCallable)
    void SetLockedState(bool bLocked);
};
