// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SW_ThrowActor.h"
#include "SW_Arrow.generated.h"

UCLASS()
class TEAM4_CH4_PROJECT_API ASW_Arrow : public ASW_ThrowActor
{
	GENERATED_BODY()

public:
	ASW_Arrow();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
