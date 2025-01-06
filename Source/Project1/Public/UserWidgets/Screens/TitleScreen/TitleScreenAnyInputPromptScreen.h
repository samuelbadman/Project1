// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserWidgets/Screens/ScreenUserWidgetBase.h"
#include "TitleScreenAnyInputPromptScreen.generated.h"

class UUIInputAction;
class AProject1HUDBase;

/**
 * 
 */
UCLASS()
class UTitleScreenAnyInputPromptScreen : public UScreenUserWidgetBase
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UUIInputAction> AnyInputUIInputAction{ nullptr };

	UPROPERTY(EditDefaultsOnly, Category = "Screens")
	TSoftClassPtr<UScreenUserWidgetBase> TitleScreenMainMenuScreenClass{ nullptr };

	// The name of the widget layer the main menu screen widget will be added to
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag PrimaryLayoutLayerNameToAddMainMenuScreenTo{};

	TObjectPtr<AProject1HUDBase> Project1HUD{ nullptr };

private:
	void NativeOnInitialized() override;
	void SetupUIInputActionEvents() override;
	// Called when the widget is manually shown on top of a widget layer stack by calling ShowTop on the layer
	void NativeOnShown() override;

	void OnAnyInputUIInputTriggered(const FUIInputActionValue& Value);
};
