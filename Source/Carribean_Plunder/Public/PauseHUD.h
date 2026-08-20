// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseHUD.generated.h"

/**
 * 
 */
UCLASS()
class CARRIBEAN_PLUNDER_API UPauseHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
    virtual void NativeConstruct() override;

    UPROPERTY(meta = (BindWidget))
    class UButton* ResumeButton;

    UPROPERTY(meta = (BindWidget))
    class UButton* SettingsButton;

    UPROPERTY(meta = (BindWidget))
    class UButton* BackButton;

    UPROPERTY(meta = (BindWidget))
    class UButton* MenuButton;

    UPROPERTY(meta = (BindWidget))
    class UWidgetSwitcher* PauseWidgetSwitcher;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup")
    FName GameplayLevelName;

private:
    UFUNCTION()
    void OnResumeClicked();

    UFUNCTION()
    void OnSettingsClicked();

    UFUNCTION()
    void OnBackClicked();

    UFUNCTION()
    void OnMenuClicked();
};
