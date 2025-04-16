// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG/Screens/ScreenUserWidgetBase.h"
#include "TitleScreenAnyInputPromptScreen.generated.h"

class AProject1PlayerControllerBase;
class AProject1HUDBase;
struct FInputActionValue;
class UPressAnyInputScreenUIInput;

/**
 * 
 */
UCLASS()
class UTitleScreenAnyInputPromptScreen : public UScreenUserWidgetBase
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	FGameplayTag UIInputKey{};

	UPROPERTY(EditDefaultsOnly)
	TSoftClassPtr<UScreenUserWidgetBase> TitleScreenMainMenuScreenClass{ nullptr };

	// The name of the widget layer the main menu screen widget will be added to
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag TitleScreenMainMenuScreenTargetLayerName{};

	TObjectPtr<AProject1PlayerControllerBase> Project1PlayerController{ nullptr };
	TObjectPtr<UPressAnyInputScreenUIInput> PressAnyInputScreenUIInput{ nullptr };
	TObjectPtr<AProject1HUDBase> Project1HUD{ nullptr };

	FDelegateHandle PressAnyInputTriggeredDelegateHandle{};

private:
	void NativeOnPushedToLayerStack() override;
	void NativeOnPoppedFromLayerStack() override;

	void OnPressAnyInputPromptAnyInputTriggered(const FInputActionValue& Value);
};
