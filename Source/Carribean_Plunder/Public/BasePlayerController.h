// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "BasePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CARRIBEAN_PLUNDER_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	// Called to bind functionality to input
	virtual void SetupInputComponent() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Mapping context
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* GlobalContext;

	// Interact input
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* InteractAction;

	// Spectate input
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* SpectateAction;

	// Interact event
	void InteractEvent(const FInputActionValue& Value);

	// Interact event
	void SpectateEvent(const FInputActionValue& Value);

private:
	// Reference to original player to keep upon changing to spectator mode
	UPROPERTY()
	ACharacter* PlayerRef;
};
