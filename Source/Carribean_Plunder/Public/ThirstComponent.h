// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ThirstComponent.generated.h"

// Creation of a delegate which takes a float
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnThirstChanged, float, Thirst, float, MaxThirst);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CARRIBEAN_PLUNDER_API UThirstComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UThirstComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Delegate for everytime thirst gets drained
	UPROPERTY(BlueprintAssignable, Category = "Thirst")
	FOnThirstChanged OnThirstChanged;

	// Function for filling thirst that broadcasts the delegate
	UFUNCTION(BlueprintCallable, Category = "Thirst")
	bool FillThirst(float Amount);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	// The max thirst the actor has
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Thirst")
	float MaxThirst = 100.f;

	// The drain rate for losing thirst
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Thirst")
	float DrainRate = 5.f;

	// The current thirst the actor has
	float CurrentThirst;
};
