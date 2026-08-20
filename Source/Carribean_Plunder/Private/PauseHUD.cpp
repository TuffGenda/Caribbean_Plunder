// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseHUD.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "BasePlayerController.h"

void UPauseHUD::NativeConstruct()
{
	Super::NativeConstruct();

	if (ResumeButton)
	{
		ResumeButton->OnClicked.AddDynamic(this, &UPauseHUD::OnResumeClicked);
	}

	if (SettingsButton)
	{
		SettingsButton->OnClicked.AddDynamic(this, &UPauseHUD::OnSettingsClicked);
	}

	if (BackButton)
	{
		BackButton->OnClicked.AddDynamic(this, &UPauseHUD::OnBackClicked);
	}

	if (MenuButton)
	{
		MenuButton->OnClicked.AddDynamic(this, &UPauseHUD::OnMenuClicked);
	}
}

void UPauseHUD::OnResumeClicked()
{
	ABasePlayerController* PC = Cast<ABasePlayerController>(GetOwningPlayer());
	
	if (PC)
	{
		PC->PauseResume();
	}
}

void UPauseHUD::OnSettingsClicked()
{
	if (PauseWidgetSwitcher)
	{
		PauseWidgetSwitcher->SetActiveWidgetIndex(1);
	}
}

void UPauseHUD::OnBackClicked()
{
	if (PauseWidgetSwitcher)
	{
		PauseWidgetSwitcher->SetActiveWidgetIndex(0);
	}
}

void UPauseHUD::OnMenuClicked()
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
