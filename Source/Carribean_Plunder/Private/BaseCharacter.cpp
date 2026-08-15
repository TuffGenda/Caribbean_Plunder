// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "StaminaComponent.h"
#include "ThirstComponent.h"
#include "HungerComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	StaminaComp = CreateDefaultSubobject<UStaminaComponent>(TEXT("StaminaComp"));
	ThirstComp = CreateDefaultSubobject<UThirstComponent>(TEXT("ThirstComp"));
	HungerComp = CreateDefaultSubobject<UHungerComponent>(TEXT("HungerComp"));
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}
