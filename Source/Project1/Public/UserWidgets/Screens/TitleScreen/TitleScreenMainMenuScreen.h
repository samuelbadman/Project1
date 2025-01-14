// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserWidgets/Screens/ScreenUserWidgetBase.h"
#include "TitleScreenMainMenuScreen.generated.h"

class UTitleScreenMainMenuButtonWidget;

/**
 * 
 */
UCLASS()
class UTitleScreenMainMenuScreen : public UScreenUserWidgetBase
{
	GENERATED_BODY()

private:
	TArray<TObjectPtr<UTitleScreenMainMenuButtonWidget>> RegisteredMenuButtons{};
	int32 ActiveMenuButtonIndex{ -1 };

public:
	UFUNCTION(BlueprintCallable)
	void RegisterMenuButtons(const TArray<UTitleScreenMainMenuButtonWidget*>& Buttons, int32 ActiveButtonIndex);

private:
	void NativeOnNavigateTriggered(const FInputActionValue& Value) override;
	void NativeOnConfirmTriggered(const FInputActionValue& Value) override;
	void NativeOnMouseMoved(const FVector2D& NewMousePosition, const FVector2D& OldMousePosition, const FVector2D& MouseMoveDelta) override;

	void ActivateButton(int32 ButtonIndex);
	void DeactivateButton(int32 ButtonIndex);
};
