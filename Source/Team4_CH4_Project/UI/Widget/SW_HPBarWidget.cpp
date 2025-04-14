// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SW_HPBarWidget.h"
#include "Components/ProgressBar.h"
#include "UI/Controller/SW_HPBarWidgetController.h"

void USW_HPBarWidget::UpdateHealthBar()
{

}

void USW_HPBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

    HealthProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HealthProgressBar")));

    USW_HPBarWidgetController* HpBarControllerRef = Cast<USW_HPBarWidgetController>(WidgetController);
    if (HpBarControllerRef)
    {
        float MaxHealth = HpBarControllerRef->GetMaxHealth();
        if (MaxHealth > 0.f)
        {
            float Health = HpBarControllerRef->GetHealth();
            float percent = Health / MaxHealth;
            HealthProgressBar->SetPercent(percent);
            UE_LOG(LogTemp, Warning, TEXT("percent : %f"), percent);
        }
    }
}

void USW_HPBarWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    UE_LOG(LogTemp, Warning, TEXT("Hp Widget Native On Initialize"));
}
