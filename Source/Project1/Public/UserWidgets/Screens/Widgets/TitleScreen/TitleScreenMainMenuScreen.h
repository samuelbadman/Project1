// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserWidgets/Screens/Widgets/ScreenUserWidgetBase.h"
#include "TitleScreenMainMenuScreen.generated.h"

class ATitleScreenPlayerController;
struct FInputActionValue;

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

private:
	void NativeOnPushedToLayerStack() override;
	void NativeOnPoppedFromLayerStack() override;

	void OnMainMenuUIConfirmTriggered(const FInputActionValue& Value);
	void OnMainMenuUINavigateTriggered(const FInputActionValue& Value);
};
