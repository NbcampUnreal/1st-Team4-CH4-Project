#include "SW_HP.h"
#include "Components/WidgetComponent.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerState.h"

void USW_HP::NativeConstruct()
{
    Super::NativeConstruct();

    if (!NameText) return;

    // Get a reference to the Player that actually owns the character this widget is attached to
    // WARNING! GETOUTER() ISN'T WidgetComponent!! FUCK MY LIFE!!!
    if (UWidgetComponent* OwningComponent = Cast<UWidgetComponent>(GetOuter()))
    {
        if (ACharacter* OwningCharacter = Cast<ACharacter>(OwningComponent->GetOwner()))
        {
            if (APlayerState* PS = OwningCharacter->GetPlayerState())
            {
                NameText->SetText(FText::FromString(PS->GetPlayerName()));
            }
            else
            {
                GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Magenta, TEXT("GetPlayerState Failed"));
            }
        }
        else
        {
            GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Magenta, TEXT("OwningCharacter Cast Failed"));
        }
    }
    else {
        GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Magenta, TEXT("WidgetComponent Cast Failed"));
    }
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
