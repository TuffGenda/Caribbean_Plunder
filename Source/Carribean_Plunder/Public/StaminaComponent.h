// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StaminaComponent.generated.h"

// Creation of a delegate which takes a float
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStaminaChanged, float, Stamina, float, MaxStamina);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CARRIBEAN_PLUNDER_API UStaminaComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStaminaComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Delegate for everythime stamina gets drained
	UPROPERTY(BlueprintAssignable, Category = "Stamina")
	FOnStaminaChanged OnStaminaChanged;

	// Function for using stamina that broadcasts the delegate
	UFUNCTION(BlueprintCallable, Category = "Stamina")
	bool UseStamina(float Amount);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stamina")
	bool RegenStamina = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stamina")
	float RegenStaminaMult = 0.f;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	// The max stamina the actor has
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stamina")
	float MaxStamina = 100.f;

	// The regen rate for recovering stamina
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stamina")
	float RegenRate = 25.0f;

	// The current stamina the actor has
	float CurrentStamina;
};
