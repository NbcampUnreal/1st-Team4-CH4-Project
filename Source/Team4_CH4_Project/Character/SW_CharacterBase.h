// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "SW_CharacterBase.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDownTimeTickDelegate, int32, Seconds);

UCLASS(Abstract)
class TEAM4_CH4_PROJECT_API ASW_CharacterBase : public ACharacter, public IAbilitySystemInterface
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

	// Skill
	UPROPERTY(EditAnywhere, Category = "Skill")
	FTimerHandle  QSkill_DownTime_TimerHandle;

	UPROPERTY(EditAnywhere, Category = "Skill")
	int32  Skill_DownTime_Remaining;

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

	// Gameplay Ability System
protected:
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const;

// skill
//public:
//	UFUNCTION(BlueprintCallable, Category = "Skill")
//	void StartDownTime(float DownTime);
//
//	
//	UPROPERTY(BlueprintAssignable, Category = "Skill")
//	FDownTimeTickDelegate OnDownTimeTick;
//
//public:
//	FTimerHandle DownTime_TimerHandle;
//	float RemainingTime;
//
//	void UpdateCooldown();
};
