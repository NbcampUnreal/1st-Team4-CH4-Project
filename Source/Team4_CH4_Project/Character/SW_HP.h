#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SW_HP.generated.h"

class UProgressBar;
class UTextBlock;

UCLASS()
class TEAM4_CH4_PROJECT_API USW_HP : public UUserWidget
{
    GENERATED_BODY()

public:
    // 체력 UI 갱신 함수
    void UpdateHealthBar(int32 CurrentHealth, int32 MaxHealth);

protected:
    virtual void NativeConstruct() override;

    UPROPERTY(meta = (BindWidget))
    UProgressBar* HealthBar;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* HealthCount;
};
