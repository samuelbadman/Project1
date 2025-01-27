// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG/Screens/Widgets/ScreenUserWidgetBase.h"
#include "TitleScreenAnyInputPromptScreen.generated.h"

class ATitleScreenPlayerController;
class AProject1HUDBase;
struct FInputActionValue;

/**
 * 
 */
UCLASS()
class UTitleScreenAnyInputPromptScreen : public UScreenUserWidgetBase
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly)
	TSoftClassPtr<UScreenUserWidgetBase> TitleScreenMainMenuScreenClass{ nullptr };

	// The name of the widget layer the main menu screen widget will be added to
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag TitleScreenMainMenuScreenTargetLayerName{};

	TObjectPtr<ATitleScreenPlayerController> TitleScreenPlayerController{ nullptr };
	TObjectPtr<AProject1HUDBase> Project1HUD{ nullptr };

	FDelegateHandle PressAnyInputTriggeredDelegateHandle{};

private:
	void NativeOnPushedToLayerStack() override;
	void NativeOnPoppedFromLayerStack() override;

	void OnPressAnyInputTriggered(const FInputActionValue& Value);
};
