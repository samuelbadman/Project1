// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG/Screens/Menus/MenuScreenBase.h"
#include "TitleScreenMainMenuScreen.generated.h"

class ATitleScreenPlayerController;
struct FInputActionValue;
class UProject1ButtonBase;
class UScrollBox;

/**
 *
 */
UCLASS()
class UTitleScreenMainMenuScreen : public UMenuScreenBase
{
	GENERATED_BODY()

private:
	TObjectPtr<ATitleScreenPlayerController> TitleScreenPlayerController{ nullptr };

	FDelegateHandle MainMenuUIConfirmTriggeredDelegateHandle{};
	FDelegateHandle MainMenuUINavigateTriggeredDelegateHandle{};

public:
	UTitleScreenMainMenuScreen();

	UFUNCTION(BlueprintCallable)
	void RegisterMenuButtons(const TArray<UProject1ButtonBase*>& Buttons, int32 DefaultHoveredButtonIndex = 0);

	UFUNCTION(BlueprintImplementableEvent)
	UScrollBox* GetScrollBox();

private:
	void NativeOnPushedToLayerStack() override;
	void NativeOnPoppedFromLayerStack() override;

	void OnMainMenuScreenConfirmTriggered(const FInputActionValue& Value);
	void OnMainMenuScreenNavigateTriggered(const FInputActionValue& Value);

	UFUNCTION()
	void OnRegisteredMenuButtonHovered(UProject1ButtonBase* ButtonHovered);

	// Call to hover the button from the main menu screen
	void HoverButton(TObjectPtr<UProject1ButtonBase> Button);
};
