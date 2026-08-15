// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class CARRIBEAN_PLUNDER_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* StaminaBar;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthBar;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* ThirstBar;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* HungerBar;

	UFUNCTION(BlueprintCallable, Category = "UI")
	void UpdateStamina(float CurrentStamina, float MaxStamina);

	UFUNCTION(BlueprintCallable, Category = "UI")
	void UpdateHealth(float CurrentHealth, float MaxHealth);

	UFUNCTION(BlueprintCallable, Category = "UI")
	void UpdateThirst(float CurrentThirst, float MaxThirst);

	UFUNCTION(BlueprintCallable, Category = "UI")
	void UpdateHunger(float CurrentHunger, float MaxHunger);
};
