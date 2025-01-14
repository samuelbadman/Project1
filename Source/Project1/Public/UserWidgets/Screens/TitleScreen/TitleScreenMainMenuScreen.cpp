// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleScreenMainMenuScreen.h"
#include "InputActionValue.h"
#include "UserWidgets/ComponentWidgets/Buttons/TitleScreenMainMenuButtonWidget.h"
#include "FunctionLibraries/Project1BlueprintFunctionLibrary.h"

void UTitleScreenMainMenuScreen::RegisterMenuButtons(const TArray<UTitleScreenMainMenuButtonWidget*>& Buttons, int32 ActiveButtonIndex)
{
	RegisteredMenuButtons = Buttons;
	ActiveMenuButtonIndex = ActiveButtonIndex;
	ActivateButton(ActiveButtonIndex);
}

void UTitleScreenMainMenuScreen::NativeOnNavigateTriggered(const FInputActionValue& Value)
{
	// Ignore navigation input if menu buttons are not registered
	if (RegisteredMenuButtons.Num() == 0)
	{
		return;
	}

	// Deactivate current active menu button
	DeactivateButton(ActiveMenuButtonIndex);

	// Flip sign of vertical input to match direction of buttons in the array
	ActiveMenuButtonIndex = UProject1BlueprintFunctionLibrary::WrapIncrementArrayIndex(
		ActiveMenuButtonIndex, 
		RegisteredMenuButtons.Num(), 
		StaticCast<int32>(Value.Get<FVector2D>().Y) * -1
	);

	// Activate button at new active button index
	ActivateButton(ActiveMenuButtonIndex);
}

void UTitleScreenMainMenuScreen::NativeOnConfirmTriggered(const FInputActionValue& Value)
{
	RegisteredMenuButtons[ActiveMenuButtonIndex]->OnActiveConfirmInput();
}

void UTitleScreenMainMenuScreen::NativeOnMouseMoved(const FVector2D& NewMousePosition, const FVector2D& OldMousePosition, const FVector2D& MouseMoveDelta)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Cyan, FString::Printf(TEXT("Title screen main menu screen On mouse moved")));
}

void UTitleScreenMainMenuScreen::ActivateButton(int32 ButtonIndex)
{
	RegisteredMenuButtons[ButtonIndex]->OnBecomeActive();
}

void UTitleScreenMainMenuScreen::DeactivateButton(int32 ButtonIndex)
{
	RegisteredMenuButtons[ButtonIndex]->OnEndActive();
}
