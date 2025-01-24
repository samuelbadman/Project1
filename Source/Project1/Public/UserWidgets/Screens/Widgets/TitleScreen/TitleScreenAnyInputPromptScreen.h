// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserWidgets/Screens/Widgets/ScreenUserWidgetBase.h"
#include "TitleScreenAnyInputPromptScreen.generated.h"

class AProject1HUDBase;

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

	TObjectPtr<AProject1HUDBase> Project1HUD{ nullptr };

private:
	void NativeOnInitialized() override;
	// Called when the widget is manually shown on top of a widget layer stack by calling ShowTop on the layer
	void NativeOnShown() override;
};
