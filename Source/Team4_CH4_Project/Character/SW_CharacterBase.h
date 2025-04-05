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

private:
    UPROPERTY(VisibleAnywhere, Replicated, Category = "Movement")
    float GroundSpeed;

    UPROPERTY(VisibleAnywhere, Category = "Movement")
    FVector Acceleration;

    UPROPERTY(VisibleAnywhere, Category = "Movement")
    FVector Velocity;

    UPROPERTY(VisibleAnywhere, Category = "Movement")
    FVector AccelerationLastFrame;

    UPROPERTY(VisibleAnywhere, Category = "Movement")
    FVector VelocityLastFrame;

    UPROPERTY(VisibleAnywhere, Replicated, Category = "Stat")
    int32 Health;

    UPROPERTY(VisibleAnywhere, Replicated, Category = "Stat")
    int32 Stamina;

public:
    UFUNCTION(BlueprintCallable)
    float GetGroundSpeed();

    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool IsMoving() const;

    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool IsJump() const;

    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool InAir() const;

    UFUNCTION(BlueprintCallable)
    void SetGroundSpeed(float _Velocity);

    void ResetCombo();
    void CheckPendingCombo();

    UFUNCTION(BlueprintCallable)
    void PlaySkillAnimation(FName SkillName);

    UFUNCTION(BlueprintCallable)
    void SetLockedState(bool bLocked);
};