// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SW_HPBarWidget.h"
#include "Components/ProgressBar.h"

void USW_HPBarWidget::UpdateHealthBar()
{
    int c = 0;
}

void USW_HPBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

    HealthProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HealthProgressBar")));

    if (!IsValid(HealthProgressBar))
    {
        UE_LOG(LogTemp, Warning, TEXT("No Hp Progress Bar"));
    }

    UE_LOG(LogTemp, Warning, TEXT("Hp Widget Native On Construct"));
}

void USW_HPBarWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    UE_LOG(LogTemp, Warning, TEXT("Hp Widget Native On Initialize"));
}
