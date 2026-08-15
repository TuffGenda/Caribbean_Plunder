// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class CARRIBEAN_PLUNDER_API UMenuHUD : public UUserWidget
{
	GENERATED_BODY()

public:
    virtual void NativeConstruct() override;

    UPROPERTY(meta = (BindWidget))
    class UButton* PlayButton;

    UPROPERTY(meta = (BindWidget))
    class UButton* CreditsButton;

    UPROPERTY(meta = (BindWidget))
    class UButton* CreditsBackButton;

    UPROPERTY(meta = (BindWidget))
    class UButton* QuitButton;

    UPROPERTY(meta = (BindWidget))
    class UWidgetSwitcher* MenuWidgetSwitcher;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup")
    FName GameplayLevelName;

private:
    UFUNCTION()
    void OnPlayClicked();

    UFUNCTION()
    void OnCreditsClicked();

    UFUNCTION()
    void OnCreditsBackClicked();

    UFUNCTION()
    void OnQuitClicked();
	
};
