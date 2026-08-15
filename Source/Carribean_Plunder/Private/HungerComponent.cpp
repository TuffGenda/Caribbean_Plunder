// Fill out your copyright notice in the Description page of Project Settings.


#include "HungerComponent.h"

// Sets default values for this component's properties
UHungerComponent::UHungerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}

// Called every frame
void UHungerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CurrentHunger >= 0.f && DrainRate)
	{
		CurrentHunger = FMath::Clamp(CurrentHunger - (DrainRate * DeltaTime), 0.f, MaxHunger);
		OnHungerChanged.Broadcast(CurrentHunger, MaxHunger);
	}
}

// Function for filling hunger that broadcasts the delegate
bool UHungerComponent::FillHunger(float Amount)
{
	if (CurrentHunger >= MaxHunger)
	{
		return false;
	}

	CurrentHunger = FMath::Clamp(CurrentHunger + Amount, 0.f, MaxHunger);

	return true;
}

// Called when the game starts
void UHungerComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHunger = MaxHunger;

}
