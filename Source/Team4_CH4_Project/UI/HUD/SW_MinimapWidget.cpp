// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_MinimapWidget.h"
#include "Components/Image.h"
#include "GameFramework/Character.h"
#include "Materials/MaterialParameterCollection.h"
#include "Materials/MaterialParameterCollectionInstance.h"

USW_MinimapWidget::USW_MinimapWidget(const FObjectInitializer& ObjectInitializer)
	: UUserWidget(ObjectInitializer)
{
	ConstructorHelpers::FObjectFinder<UMaterialParameterCollection> MPCFinder(TEXT("/Game/UI/HUD/Minimap/MPC_Minimap.MPC_Minimap"));
	if (MPCFinder.Succeeded())
	{
		MPCMinimap = MPCFinder.Object;
	}

	CaptureOffsetX = 280.f;
	CaptureOffsetY = 2403.f;
	MinimapSize = 250.f;
}

void USW_MinimapWidget::UpdateMinimap()
{
	if (!GetWorld() || GetWorld()->bIsTearingDown) return;
	if (!MinimapImage || !PlayerMarker) return;
	
	if (APlayerController* PlayerController = GetOwningPlayer())
	{
		if (ACharacter* Character = PlayerController->GetCharacter())
		{
			if (UMaterialParameterCollectionInstance* MPCInstance = GetWorld()->GetParameterCollectionInstance(MPCMinimap))
			{
				float XPos = Character->GetActorLocation().X + CaptureOffsetX;
				float YPos = Character->GetActorLocation().Y + CaptureOffsetY;
				MPCInstance->SetScalarParameterValue(FName("XPos"), XPos);
				MPCInstance->SetScalarParameterValue(FName("YPos"), YPos);
				
				float CharacterYaw = static_cast<float>(Character->GetActorRotation().Yaw);
				PlayerMarker->SetRenderTransformAngle(CharacterYaw);
			}
		}
	}
}
