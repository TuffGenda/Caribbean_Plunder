// Fill out your copyright notice in the Description page of Project Settings.


#include "ThirstComponent.h"

// Sets default values for this component's properties
UThirstComponent::UThirstComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}

// Called every frame
void UThirstComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CurrentThirst >= 0.f && DrainRate)
	{
		CurrentThirst = FMath::Clamp(CurrentThirst - (DrainRate * DeltaTime), 0.f, MaxThirst);
		OnThirstChanged.Broadcast(CurrentThirst, MaxThirst);
	}
}

// Function for filling thirst that broadcasts the delegate
bool UThirstComponent::FillThirst(float Amount)
{
	if (CurrentThirst >= MaxThirst)
	{
		return false;
	}

	CurrentThirst = FMath::Clamp(CurrentThirst + Amount, 0.f, MaxThirst);

	return true;
}

// Called when the game starts
void UThirstComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentThirst = MaxThirst;
	
}
