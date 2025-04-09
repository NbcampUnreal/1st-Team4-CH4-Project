// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SW_PlayerInfoWidget.h"
#include "../CharacterData/SW_CharacterType.h"
#include "SW_SquadInfoWidget.generated.h"

UCLASS()
class TEAM4_CH4_PROJECT_API USW_SquadInfoWidget : public USW_PlayerInfoWidget
{
	GENERATED_BODY()
	
public:
	virtual void SetThumbnailByType(ECharacterType Type) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* HealthBar;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* UsernameText;
};
