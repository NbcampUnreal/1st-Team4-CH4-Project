#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SW_PlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class TEAM4_CH4_PROJECT_API ASW_PlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    ASW_PlayerController();

public:
    virtual void BeginPlay() override;
    virtual void SetupInputComponent() override;
    virtual void Tick(float DeltaTime) override;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    UInputMappingContext* InputMappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    UInputAction* MoveAction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    UInputAction* JumpAction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    UInputAction* ComboAttackAction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    UInputAction* DashSkillAction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    UInputAction* NormalSkillAction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    UInputAction* SpecialSkillAction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    UInputAction* JumpAttackAction;

public:
    void PlayerMove(const FInputActionValue& _InputValue);
    void PlayerJump(const FInputActionValue& _InputValue);
    void ComboAttack(const FInputActionValue& InputValue);
    void JumpAttack(const FInputActionValue& InputValue);
    void NormalSkill(const FInputActionValue& InputValue);
    void SpecialSkill(const FInputActionValue& InputValue);
    void DashSkill(const FInputActionValue& InputValue);
};