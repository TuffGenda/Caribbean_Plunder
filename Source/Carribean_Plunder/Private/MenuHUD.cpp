// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuHUD.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UMenuHUD::NativeConstruct()
{
	Super::NativeConstruct();

	if (PlayButton)
	{
		PlayButton->OnClicked.AddDynamic(this, &UMenuHUD::OnPlayClicked);
	}

    if (SettingsButton)
    {
        SettingsButton->OnClicked.AddDynamic(this, &UMenuHUD::OnSettingsClicked);
    }

    if (SettingsBackButton)
    {
        SettingsBackButton->OnClicked.AddDynamic(this, &UMenuHUD::OnBackClicked);
    }

	if (CreditsButton)
	{
		CreditsButton->OnClicked.AddDynamic(this, &UMenuHUD::OnCreditsClicked);
	}

    if (CreditsBackButton)
    {
        CreditsBackButton->OnClicked.AddDynamic(this, &UMenuHUD::OnBackClicked);
    }

	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &UMenuHUD::OnQuitClicked);
	}
}

void UMenuHUD::OnPlayClicked()
{
    if (!GameplayLevelName.IsNone())
    {
        APlayerController* PC = GetOwningPlayer();
        if (PC)
        {
            FInputModeGameOnly InputModeData;
            PC->SetInputMode(InputModeData);
            PC->bShowMouseCursor = false;
        }

        UGameplayStatics::OpenLevel(this, GameplayLevelName);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("GameplayLevelName is not set in the Main Menu Widget!"));
    }
}

void UMenuHUD::OnSettingsClicked()
{
    if (MenuWidgetSwitcher)
    {
        MenuWidgetSwitcher->SetActiveWidgetIndex(1);
    }
}

void UMenuHUD::OnCreditsClicked()
{
    if (MenuWidgetSwitcher)
    {
        MenuWidgetSwitcher->SetActiveWidgetIndex(2);
    }
}

void UMenuHUD::OnBackClicked()
{
    if (MenuWidgetSwitcher)
    {
        MenuWidgetSwitcher->SetActiveWidgetIndex(0);
    }
}

void UMenuHUD::OnQuitClicked()
{
    UKismetSystemLibrary::QuitGame(
        this,
        GetOwningPlayer(),
        EQuitPreference::Quit,
        false
    );
}
