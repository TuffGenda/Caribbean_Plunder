// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Called to bind functionality to input
void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Setup action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Interaction
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ABasePlayerController::InteractEvent);
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
