// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SW_HPBarWidget.h"
#include "Components/ProgressBar.h"
#include "UI/Controller/SW_HPBarWidgetController.h"

void USW_HPBarWidget::NativeConstruct()
{
	Super::NativeConstruct();
    
    HPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPProgressBar")));

    //HPProgressBar->SetPercent(0.8f);

    USW_HPBarWidgetController* HpBarControllerRef = Cast<USW_HPBarWidgetController>(WidgetController);
    if (HpBarControllerRef)
    {
        // 델리게이트 바인딩
        HpBarControllerRef->OnHealthChanged.AddDynamic(this, &USW_HPBarWidget::ChangePercent);
        HpBarControllerRef->OnMaxHealthChanged.AddDynamic(this, &USW_HPBarWidget::ChangePercent);

        // 최초값 적용 (BroadcastInitialValue()가 실행될 때 위 delegate 호출됨)
        HpBarControllerRef->BroadcastInitialValue();
        HpBarControllerRef->BindCallbacksToDependencies();
    }
}

void USW_HPBarWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    UE_LOG(LogTemp, Warning, TEXT("Hp Widget Native On Initialize"));
}

void USW_HPBarWidget::ChangePercent(float _Health, float _MaxHealth)
{
    if (!HPProgressBar)
    {
        UE_LOG(LogTemp, Error, TEXT("HPProgressBar is NULL! Check Widget name or binding"));
    }

    float percent = _Health / _MaxHealth;

    HPProgressBar->SetPercent(percent);
    UE_LOG(LogTemp, Warning, TEXT("percent : %f"), percent);
}