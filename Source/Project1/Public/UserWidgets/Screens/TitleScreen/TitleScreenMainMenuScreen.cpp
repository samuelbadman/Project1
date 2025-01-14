// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleScreenMainMenuScreen.h"
#include "InputActionValue.h"
#include "UserWidgets/ComponentWidgets/Buttons/TitleScreenMainMenuButtonWidget.h"
#include "FunctionLibraries/Project1BlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

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

	SetActiveMenuButtonIndex(UProject1BlueprintFunctionLibrary::WrapIncrementArrayIndex(
		ActiveMenuButtonIndex,
		RegisteredMenuButtons.Num(),
		StaticCast<int32>(Value.Get<FVector2D>().Y) * -1
	));
}

void UTitleScreenMainMenuScreen::NativeOnConfirmTriggered(const FInputActionValue& Value)
{
	RegisteredMenuButtons[ActiveMenuButtonIndex]->Press();
}

void UTitleScreenMainMenuScreen::NativeOnMouseMoved(const FVector2D& NewMousePosition, const FVector2D& OldMousePosition, const FVector2D& MouseMoveDelta)
{
	int32 NewActiveButtonIndex{ INDEX_NONE };

	// For each button in the menu, check if the mouse has moved over it and activate the button if so
	for (TObjectPtr<UTitleScreenMainMenuButtonWidget> Button : RegisteredMenuButtons)
	{
		if (Button->IsMouseOver(NewMousePosition))
		{
			const int32 ButtonIndex{ RegisteredMenuButtons.Find(Button) };
			if (ButtonIndex == INDEX_NONE)
			{
				continue;
			}

			NewActiveButtonIndex = ButtonIndex;
		}
	}

	SetActiveMenuButtonIndex(NewActiveButtonIndex);
}

void UTitleScreenMainMenuScreen::NativeOnLeftClickTriggered(const FInputActionValue& Value)
{
	// Select the active button if the mouse is over it
	const TObjectPtr<UTitleScreenMainMenuButtonWidget> ActiveMenuButton{ GetActiveMenuButton() };

	FVector2D MousePosition{};
	UGameplayStatics::GetPlayerController(this, 0)->GetMousePosition(MousePosition.X, MousePosition.Y);

	if (ActiveMenuButton->IsMouseOver(MousePosition))
	{
		ActiveMenuButton->Press();
	}
}

void UTitleScreenMainMenuScreen::ActivateButton(int32 ButtonIndex)
{
	RegisteredMenuButtons[ButtonIndex]->OnBecomeActive();
}

void UTitleScreenMainMenuScreen::DeactivateButton(int32 ButtonIndex)
{
	RegisteredMenuButtons[ButtonIndex]->OnEndActive();
}

void UTitleScreenMainMenuScreen::SetActiveMenuButtonIndex(int32 NewActiveButtonIndex)
{
	if (ActiveMenuButtonIndex == NewActiveButtonIndex)
	{
		return;
	}

	if (!RegisteredMenuButtons.IsValidIndex(NewActiveButtonIndex))
	{
		return;
	}

	// Deactivate current active menu button
	DeactivateButton(ActiveMenuButtonIndex);

	// Update index
	ActiveMenuButtonIndex = NewActiveButtonIndex;

	// Activate button at new active button index
	ActivateButton(NewActiveButtonIndex);
}
