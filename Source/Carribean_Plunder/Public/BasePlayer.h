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

	// Movement event
	void MoveEvent(const FInputActionValue& Value);

	// Look event
	void LookEvent(const FInputActionValue& Value);
};
