// Fill out your copyright notice in the Description page of Project Settings.

#include "SW_Arrow.h"

ASW_Arrow::ASW_Arrow()
{
	MoveSpeed = 2500.f;  
	LifeSpan = 3.f;      
	Damage = 20.f;      
}

void ASW_Arrow::BeginPlay()
{
	Super::BeginPlay();
}

void ASW_Arrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
