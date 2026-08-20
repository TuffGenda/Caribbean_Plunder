// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpectatorPawn.h"
#include "BasePlayer.h"
#include "PlayerHUD.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

// Called to bind functionality to input
void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Setup action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Interaction
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ABasePlayerController::InteractEvent);

		// Spectate
		EnhancedInputComponent->BindAction(SpectateAction, ETriggerEvent::Started, this, &ABasePlayerController::SpectateEvent);

		// Pause
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Started, this, &ABasePlayerController::PauseEvent);
	}
}

void ABasePlayerController::PauseResume()
{
	if (Paused)
	{
		bShowMouseCursor = false;
		bEnableClickEvents = false;
		bEnableMouseOverEvents = false;

		SetInputMode(FInputModeGameOnly());

		UGameplayStatics::SetGamePaused(GetWorld(), false);

		PauseWidgetInstance->RemoveFromParent();
		PauseWidgetInstance = nullptr;

		Paused = false;
	}
	else
	{
		bShowMouseCursor = true;
		bEnableClickEvents = true;
		bEnableMouseOverEvents = true;

		FInputModeGameAndUI InputModeData;
		InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

		SetInputMode(InputModeData);

		UGameplayStatics::SetGamePaused(GetWorld(), true);

		if (PauseWidgetClass)
		{
			PauseWidgetInstance = CreateWidget<UUserWidget>(this, PauseWidgetClass);
			if (PauseWidgetInstance)
			{
				PauseWidgetInstance->AddToViewport();

				Paused = true;
			}
		}
	}
}

// Called when the game starts or when spawned
void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Add the global input mapping to the controls
	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
		{
			if (GlobalContext)
			{
				Subsystem->AddMappingContext(GlobalContext, 0);
			}
		}
	}
}

// Interact event
void ABasePlayerController::InteractEvent(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Interaction Action Pressed!"));
}

void ABasePlayerController::SpectateEvent(const FInputActionValue& Value)
{
	ASpectatorPawn* Spectator = GetSpectatorPawn();

    if (Spectator == nullptr)
    {
        ACharacter* PlayerChar = GetCharacter();
        if (PlayerChar)
		{
            PlayerRef = Cast<ABasePlayer>(PlayerChar);
			PlayerHUDRef = PlayerRef->PlayerHUD;

			PlayerRef->PlayerHUD->RemoveFromParent();

			if (PlayerRef && PlayerHUDRef)
			{
				ChangeState(NAME_Spectating);
			}
        }
    }
    else
    {
		ChangeState(NAME_Playing);

        if (PlayerRef && PlayerHUDRef)
        {
			PlayerHUDRef->AddToViewport();

            Possess(PlayerRef);
        }

        SetSpectatorPawn(nullptr);
		Spectator->Destroy();
    }
}

// Pause event
void ABasePlayerController::PauseEvent(const FInputActionValue& Value)
{
	PauseResume();
}
