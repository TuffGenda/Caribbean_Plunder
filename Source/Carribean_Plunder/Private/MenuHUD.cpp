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

	if (CreditsButton)
	{
		CreditsButton->OnClicked.AddDynamic(this, &UMenuHUD::OnCreditsClicked);
	}

    if (CreditsBackButton)
    {
        CreditsBackButton->OnClicked.AddDynamic(this, &UMenuHUD::OnCreditsBackClicked);
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

void UMenuHUD::OnCreditsClicked()
{
    if (MenuWidgetSwitcher)
    {
        MenuWidgetSwitcher->SetActiveWidgetIndex(1);
    }
}

void UMenuHUD::OnCreditsBackClicked()
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
