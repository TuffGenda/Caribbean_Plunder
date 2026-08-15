// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuPlayerController.h"
#include "Blueprint/UserWidget.h"

void AMenuPlayerController::BeginPlay()
{
    Super::BeginPlay();

    bShowMouseCursor = true;
    bEnableClickEvents = true;
    bEnableMouseOverEvents = true;

    FInputModeUIOnly InputModeData;
    InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

    SetInputMode(InputModeData);

    if (MenuWidgetClass)
    {
        MenuWidgetInstance = CreateWidget<UUserWidget>(this, MenuWidgetClass);
        if (MenuWidgetInstance)
        {
            MenuWidgetInstance->AddToViewport();
        }
    }
}
