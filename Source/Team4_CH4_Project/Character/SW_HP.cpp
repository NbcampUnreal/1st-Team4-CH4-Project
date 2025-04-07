#include "SW_HP.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void USW_HP::NativeConstruct()
{
    Super::NativeConstruct();
}

void USW_HP::UpdateHealthBar(int32 CurrentHealth, int32 MaxHealth)
{
    if (HealthBar)
    {
        float Percent = (MaxHealth > 0) ? (float)CurrentHealth / (float)MaxHealth : 0.f;
        HealthBar->SetPercent(FMath::Clamp(Percent, 0.f, 1.f));
    }

    if (HealthCount)
    {
        FString Text = FString::Printf(TEXT("%d / %d"), CurrentHealth, MaxHealth);
        HealthCount->SetText(FText::FromString(Text));
    }
}
