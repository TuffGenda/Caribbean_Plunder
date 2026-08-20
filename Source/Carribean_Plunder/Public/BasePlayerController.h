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

	void PauseResume();

	bool Paused = false;

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

	// Pause input
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* PauseAction;

	// Interact event
	void InteractEvent(const FInputActionValue& Value);

	// Spectate event
	void SpectateEvent(const FInputActionValue& Value);

	// Pause event
	void PauseEvent(const FInputActionValue& Value);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<class UUserWidget> PauseWidgetClass;

	UPROPERTY()
	UUserWidget* PauseWidgetInstance;

private:
	// Reference to original player to keep upon changing to spectator mode
	UPROPERTY()
	class ABasePlayer* PlayerRef;

	UPROPERTY()
	class UPlayerHUD* PlayerHUDRef;

};
