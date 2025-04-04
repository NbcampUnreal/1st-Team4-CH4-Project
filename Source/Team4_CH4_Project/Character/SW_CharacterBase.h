#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "SW_CharacterBase.generated.h"

class USpringArmComponent; 
class UCameraComponent;

UCLASS()
class TEAM4_CH4_PROJECT_API ASW_CharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASW_CharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	// 각 캐릭터마다 InputAction 함수용 virtaul
	virtual void Player_Move(const FInputActionValue& _InputValue);
	virtual void Player_Jump(const FInputActionValue& _InputValue);

	// 캐릭터 공통된 공격 애니메이션 재생용
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

private:
	// Movement Value
	UPROPERTY(VisibleAnywhere, Replicated,  Category = "Movement")
	float GroundSpeed;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	FVector Acceleration;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	FVector Velocity;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	FVector AccelerationLastFrame;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	FVector VelocityLastFrame;

	// Stat Value
	UPROPERTY(VisibleAnywhere, Replicated, Category = "Stat")
	int32 Health;

	UPROPERTY(VisibleAnywhere, Replicated, Category = "Stat")
	int32 Stamina;

public:
	UFUNCTION(BlueprintCallable)
	float GetGroundSpeed();

	UFUNCTION(BlueprintCallable)
	void SetGroundSpeed(float _Velocity);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsMoving() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsJump() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool InAir() const;
};
