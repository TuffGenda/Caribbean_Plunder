// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HungerComponent.generated.h"

// Creation of a delegate which takes a float
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHungerChanged, float, Hunger, float, MaxHunger);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CARRIBEAN_PLUNDER_API UHungerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHungerComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Delegate for everytime hunger gets drained
	UPROPERTY(BlueprintAssignable, Category = "Hunger")
	FOnHungerChanged OnHungerChanged;

	// Function for filling hunger that broadcasts the delegate
	UFUNCTION(BlueprintCallable, Category = "Hunger")
	bool FillHunger(float Amount);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// The max hunger the actor has
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hunger")
	float MaxHunger = 100.f;

	// The drain rate for losing hunger
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hunger")
	float DrainRate = 5.f;

	// The current hunger the actor has
	float CurrentHunger;
};
