#include "Team4_CH4_Project/Game/GameMode/SW_GameMode.h"
#include "Team4_CH4_Project/Game/GameState/SW_GameState.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

ASW_GameMode::ASW_GameMode()
{
	/*static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
if (PlayerPawnBPClass.Class != NULL)
{
	DefaultPawnClass = PlayerPawnBPClass.Class;
}

static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonPlayerController"));
if (PlayerControllerBPClass.Class != NULL)
{
	PlayerControllerClass = PlayerControllerBPClass.Class;
}
*/
	// ResultWidgetClass는 에디터에서 할당
}

void ASW_GameMode::HandleGameOver()
{
	if (HasAuthority() && !bGameOverHandled)
	{
		bGameOverHandled = true;
		ShowResultWidget();
	}
}

void ASW_GameMode::BeginPlay()
{
	Super::BeginPlay();
	// 게임 스테이트 얻기
	UWorld* ThisWorld = GetWorld();
	if (ASW_GameState* TempGameState = Cast<ASW_GameState>(GetWorld()->GetGameState()))
	{
		TempGameState->RoundDuration = 240.0f; // C++에서 기본값 설정 가능
		TempGameState->SetRoundTime(TempGameState->RoundDuration);
	}
}

USW_TestCharacterClassInfo* ASW_GameMode:: GetCharacterClassDefaultInfo() const
{
	return ClassDefaults;
}

void ASW_GameMode::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);

	int Controllers = GetWorld()->GetNumPlayerControllers();
	UE_LOG(LogTemp, Warning, TEXT("The PlayerController value is: %d"), Controllers);
}

void ASW_GameMode::ShowResultWidget()
{
	if (HasAuthority() && ResultWidgetClass)
	{
		/*for (APlayerController* PC : UGameplayStatics::GetAllPlayerControllers(this))
		{
			if (PC && PC->IsLocalPlayerController())
			{
				UUserWidget* ResultWidget = CreateWidget<UUserWidget>(PC, ResultWidgetClass);
				if (ResultWidget)
				{
					ResultWidget->AddToViewport();
					// 필요하다면 결과 위젯에 정보 전달 (GameState 참조 등)
					PC->bShowMouseCursor = true;
					PC->SetInputMode(FInputModeUIOnly::FInputModeUIOnly());
				}
			}
		}
		*/
	}
}

