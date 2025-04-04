// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SW_CharacterBase.generated.h"

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
