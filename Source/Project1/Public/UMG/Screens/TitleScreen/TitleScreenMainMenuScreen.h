// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG/Screens/ScreenUserWidgetBase.h"
#include "TitleScreenMainMenuScreen.generated.h"

class AProject1PlayerControllerBase;
struct FInputActionValue;
class UScrollBox;
class UButtonMenuComponent;
class UMainMenuScreenUIInput;
class UProject1ButtonBase;

/**
 *
 */
UCLASS()
class UTitleScreenMainMenuScreen : public UScreenUserWidgetBase
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	FGameplayTag UIInputKey{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UButtonMenuComponent> ButtonMenuComponent;

	TObjectPtr<AProject1PlayerControllerBase> Project1PlayerController{ nullptr };
	TObjectPtr<UMainMenuScreenUIInput> MainMenuScreenUIInput{ nullptr };

	FDelegateHandle MainMenuUIConfirmTriggeredDelegateHandle{};
	FDelegateHandle MainMenuUINavigateTriggeredDelegateHandle{};

public:
	UTitleScreenMainMenuScreen();

	UFUNCTION(BlueprintImplementableEvent)
	UScrollBox* GetScrollBox();

	UFUNCTION(BlueprintImplementableEvent)
	UProject1ButtonBase* GetContinueButton();

	UFUNCTION(BlueprintImplementableEvent)
	UProject1ButtonBase* GetFirstMenuButtonWithoutContinue();

	UFUNCTION(BlueprintImplementableEvent)
	UProject1ButtonBase* GetLastMenuButton();

private:
	void NativeOnPushedToLayerStack() override;
	void NativeOnPoppedFromLayerStack() override;

	void OnConfirmTriggered(const FInputActionValue& Value);
	void OnNavigateTriggered(const FInputActionValue& Value);
};
