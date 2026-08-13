// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "InputActionValue.h"
#include "BasePlayer.generated.h"

UCLASS()
class CARRIBEAN_PLUNDER_API ABasePlayer : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	// Sets default values for this character's properties
	ABasePlayer();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Overridden jump function for use with stamina
	virtual void Jump() override;

	// Mapping context
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* CharacterMovementContext;

	// Movement input
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	// Look input
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	// Jump input
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	// Sprint input
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* SprintAction;

	// Default walking speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float WalkSpeed = 1000.f;

	// Default sprinting speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float SprintSpeed = 1500.f;

	// Default sprinting cost
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float SprintCost = 1.f;

	// Default jumping cost
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float JumpCost = 10.f;

	// Movement event
	void MoveEvent(const FInputActionValue& Value);

	// Look event
	void LookEvent(const FInputActionValue& Value);

	// Sprint events
	void SprintEvent(const FInputActionValue& Value);
	void StopSprintEvent(const FInputActionValue& Value);

	// Stamina change event
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void StaminaChange(float CurrentStamina, float MaxStamina);

};
