// Fill out your copyright notice in the Description page of Project Settings.


#include "StaminaComponent.h"

// Sets default values for this component's properties
UStaminaComponent::UStaminaComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}

// Called every frame
void UStaminaComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CurrentStamina < MaxStamina && RegenStamina)
	{
		CurrentStamina = FMath::Clamp(CurrentStamina + (RegenRate * RegenStaminaMult * DeltaTime), 0.f, MaxStamina);
		OnStaminaChanged.Broadcast(CurrentStamina, MaxStamina);
	}

	RegenStaminaMult = 2.f;
}

// Function for using stamina that broadcasts the delegate
bool UStaminaComponent::UseStamina(float Amount)
{
	if (CurrentStamina < Amount)
	{
		return false;
	}

	if (CurrentStamina <= 0.0f)
	{
		return false;
	}

	CurrentStamina -= Amount;
	OnStaminaChanged.Broadcast(CurrentStamina, MaxStamina);

	return true;
}

// Called when the game starts
void UStaminaComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentStamina = MaxStamina;

}
