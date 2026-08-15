// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"

void UPlayerHUD::UpdateStamina(float CurrentStamina, float MaxStamina)
{
    if (StaminaBar && MaxStamina > 0.f)
    {
        StaminaBar->SetPercent(CurrentStamina / MaxStamina);
    }
}

void UPlayerHUD::UpdateHealth(float CurrentHealth, float MaxHealth)
{
    if (HealthBar && MaxHealth > 0.f)
    {
        HealthBar->SetPercent(CurrentHealth / MaxHealth);
    }
}

void UPlayerHUD::UpdateThirst(float CurrentThirst, float MaxThirst)
{
    if (ThirstBar && MaxThirst > 0.f)
    {
        ThirstBar->SetPercent(CurrentThirst / MaxThirst);
    }
}

void UPlayerHUD::UpdateHunger(float CurrentHunger, float MaxHunger)
{
    if (HungerBar && MaxHunger > 0.f)
    {
        HungerBar->SetPercent(CurrentHunger / MaxHunger);
    }
}
