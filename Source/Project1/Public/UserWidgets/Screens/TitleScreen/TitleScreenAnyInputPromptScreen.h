// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserWidgets/Screens/ScreenUserWidgetBase.h"
#include "TitleScreenAnyInputPromptScreen.generated.h"

class UUIInputAction;

/**
 * 
 */
UCLASS()
class UTitleScreenAnyInputPromptScreen : public UScreenUserWidgetBase
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UUIInputAction> AnyInputUIInputAction{ nullptr };

private:
	void SetupUIInputActionEvents() override;
	// Called when the widget is manually shown on top of a widget layer stack by calling ShowTop on the layer
	void NativeOnShown() override;

	void OnAnyInputUIInput(const FUIInputActionValue& Value);
};
