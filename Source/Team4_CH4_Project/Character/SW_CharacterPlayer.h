// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SW_CharacterBase.h"
#include "InputActionValue.h"
#include "SW_CharacterPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class TEAM4_CH4_PROJECT_API ASW_CharacterPlayer : public ASW_CharacterBase
{
	GENERATED_BODY()
public:
	ASW_CharacterPlayer();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float SpringBoomLength;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UFUNCTION(BlueprintCallable)
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	virtual void Player_Move(const FInputActionValue& _InputValue);
};
