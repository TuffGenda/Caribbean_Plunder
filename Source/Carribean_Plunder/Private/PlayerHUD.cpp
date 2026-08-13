// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"

void UPlayerHUD::UpdateStamina(float CurrentStamina, float MaxStamina)
{
    if (StaminaBar && MaxStamina > 0.0f)
    {
        StaminaBar->SetPercent(CurrentStamina / MaxStamina);
    }
}
