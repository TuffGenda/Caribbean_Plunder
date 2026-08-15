// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "StaminaComponent.h"
#include "ThirstComponent.h"
#include "HungerComponent.h"
#include "PlayerHUD.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ABasePlayer::ABasePlayer()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Set default movement speed
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

// Called to bind functionality to input
void ABasePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	// Setup action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Movement
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABasePlayer::MoveEvent);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABasePlayer::LookEvent);

		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ABasePlayer::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Sprinting
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &ABasePlayer::SprintEvent);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &ABasePlayer::StopSprintEvent);
	}
}

// Called when the game starts or when spawned
void ABasePlayer::BeginPlay()
{
	Super::BeginPlay();

	// Add the input mapping to the player
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			if (CharacterMovementContext)
			{
				Subsystem->AddMappingContext(CharacterMovementContext, 0);
			}
		}
	}

	if (PlayerHUD)
	{
		PlayerHUD->AddToViewport();

		if (StaminaComp)
		{
			StaminaComp->OnStaminaChanged.AddDynamic(PlayerHUD, &UPlayerHUD::UpdateStamina);
			PlayerHUD->UpdateStamina(100.f, 100.f);
		}

		/*if (HealthComp)
		{
			HealthComp->OnHealthChanged.AddDynamic(PlayerHUD, &UPlayerHUD::UpdateHealth);
			PlayerHUD->UpdateHealth(100.f, 100.f);
		}*/

		if (ThirstComp)
		{
			ThirstComp->OnThirstChanged.AddDynamic(PlayerHUD, &UPlayerHUD::UpdateThirst);
			PlayerHUD->UpdateThirst(100.f, 100.f);
		}

		if (HungerComp)
		{
			HungerComp->OnHungerChanged.AddDynamic(PlayerHUD, &UPlayerHUD::UpdateHunger);
			PlayerHUD->UpdateHunger(100.f, 100.f);
		}
	}
}

void ABasePlayer::Jump()
{
	if (StaminaComp && StaminaComp->UseStamina(JumpCost))
	{
		Super::Jump();

		StaminaComp->RegenStaminaMult = 1.f;
	}
}

// Movement event
void ABasePlayer::MoveEvent(const FInputActionValue& Value)
{
	// Get FVector2D from input
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// Find forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// Get forward
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// Get right
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// Add movement
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);

		StaminaComp->RegenStaminaMult = 1.f;
	}
}

// Look event
void ABasePlayer::LookEvent(const FInputActionValue& Value)
{
	// Get FVector2D from input
	const FVector2D LookVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// Add input to Controller
		AddControllerYawInput(LookVector.X);
		AddControllerPitchInput(LookVector.Y);
	}
}

// Sprint events
void ABasePlayer::SprintEvent(const FInputActionValue& Value)
{
	if (StaminaComp && StaminaComp->UseStamina(SprintCost))
	{
		// Set sprinting movement speed
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;

		StaminaComp->RegenStamina = true;
		StaminaComp->RegenStaminaMult = 1.f;
	}
	else
	{
		StopSprintEvent(Value);
	}
}
void ABasePlayer::StopSprintEvent(const FInputActionValue& Value)
{
	// Restore walking movement speed
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

	if (StaminaComp)
	{
		StaminaComp->RegenStamina = true;
	}
}
