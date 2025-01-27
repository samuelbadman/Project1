// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG/Screens/Widgets/ScreenUserWidgetBase.h"
#include "TitleScreenMainMenuScreen.generated.h"

class ATitleScreenPlayerController;
struct FInputActionValue;
class UProject1ButtonBase;

/**
 *
 */
UCLASS()
class UTitleScreenMainMenuScreen : public UScreenUserWidgetBase
{
	GENERATED_BODY()

private:
	TObjectPtr<ATitleScreenPlayerController> TitleScreenPlayerController{ nullptr };

	FDelegateHandle MainMenuUIConfirmTriggeredDelegateHandle{};
	FDelegateHandle MainMenuUINavigateTriggeredDelegateHandle{};

	TObjectPtr<UProject1ButtonBase> CurrentHoveredButton{ nullptr };

public:
	UFUNCTION(BlueprintCallable)
	void RegisterMenuButtons(const TArray<UProject1ButtonBase*>& Buttons, int32 DefaultHoveredButtonIndex = 0);

private:
	void NativeOnPushedToLayerStack() override;
	void NativeOnPoppedFromLayerStack() override;

	void OnMainMenuUIConfirmTriggered(const FInputActionValue& Value);
	void OnMainMenuUINavigateTriggered(const FInputActionValue& Value);

	UFUNCTION()
	void OnRegisteredMenuButtonHovered(UProject1ButtonBase* ButtonHovered);

	// Call to hover the button from the main menu screen
	void HoverButton(TObjectPtr<UProject1ButtonBase> Button);

	// Sets the variable that tracks which button is hovered
	void SetHoveredButton(TObjectPtr<UProject1ButtonBase> NewHoveredButton);
};
