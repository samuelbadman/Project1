// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonMenuComponent.h"
#include "UMG/Components/Buttons/Project1ButtonBase.h"
#include "FunctionLibraries/Project1MathLibrary.h"

UButtonMenuComponent::UButtonMenuComponent()
	: bFocusButtonOnMouseCursorEnter(true),
	bUnfocusButtonOnMouseCursorLeave(true),
	RegisteredButtons({}),
	FocusedButton(nullptr),
	FocusedButtonIndex(0)
{
}

void UButtonMenuComponent::RegisterMenuButtons(const TArray<UProject1ButtonBase*>& Buttons, bool ActivateButtonMouseInput)
{
	RegisteredButtons.Append(&Buttons[0], Buttons.Num());

	// Iterating through in Buttons here instead of RegisteredButtons so that delegates are only registered for the new buttons being appended to the registered buttons array.
	// Existing buttons already have these delegates registered and cannot and should not be registered again
	for (const TObjectPtr<UProject1ButtonBase>& Button : Buttons)
	{
		if (ActivateButtonMouseInput)
		{
			Button->SetGenerateHoverEvents(false);

			Button->OnMouseCursorOver.AddDynamic(this, &UButtonMenuComponent::OnMouseCursorOverMenuButton);
			Button->OnMouseCursorLeft.AddDynamic(this, &UButtonMenuComponent::OnMouseCursorLeftMenuButton);

			Button->ActivateMouseInput();
		}
	}
}

void UButtonMenuComponent::FocusButton(UProject1ButtonBase* Button)
{
	const int32 NewFocusedButtonIndex{ RegisteredButtons.Find(Button) };
	
	// Button must be registered with the component to be able to be focused
	if (NewFocusedButtonIndex == INDEX_NONE)
	{
		return;
	}

	if (IsValid(FocusedButton))
	{
		FocusedButton->MakeUnhovered();
	}

	FocusedButton = Button;
	// Need to track the index of the focused button in the registered array to support navigating through the array with an index offset
	FocusedButtonIndex = NewFocusedButtonIndex;
	Button->MakeHovered();
}

TObjectPtr<UProject1ButtonBase> UButtonMenuComponent::NavigateMenu(const EWidgetNavigationDirection Direction)
{
	// Cannot navigate if the menu does not have a focused button
	if (!IsValid(FocusedButton))
	{
		return nullptr;
	}

	// Get button in direction to navigate to
	const TObjectPtr<UProject1ButtonBase> NavigationButton{ Cast<UProject1ButtonBase>(FocusedButton->GetNavigationWidget(Direction).Get()) };

	// Cannot navigate if the navigation button is invalid
	if (!IsValid(NavigationButton))
	{
		return nullptr;
	}

	// Navigate widgets and set the menu focus to the widget navigated to
	FocusedButton->NavigateFromWidget(NavigationButton);
	FocusButton(NavigationButton);

	return NavigationButton;
}

TObjectPtr<UProject1ButtonBase> UButtonMenuComponent::NavigateMenu(int32 Amount, bool Wrap)
{
	// Current focused button index must be in range of registered buttons array before navigating
	if (!RegisteredButtons.IsValidIndex(FocusedButtonIndex))
	{
		return nullptr;
	}

	// Get new button to focus from offset index in array optionally wrapping around
	int32 NewFocusedButtonIndex{ INDEX_NONE };

	NewFocusedButtonIndex = (Wrap) ? 
		UProject1MathLibrary::WrapIncrementArrayIndex(FocusedButtonIndex, RegisteredButtons.Num(), Amount) :
		FMath::Clamp(FocusedButtonIndex + Amount, 0, RegisteredButtons.Num() - 1);

	const TObjectPtr<UProject1ButtonBase> NewFocusedButton{ RegisteredButtons[NewFocusedButtonIndex] };

	if (FocusedButton == NewFocusedButton)
	{
		// New focused button is the current focused button so, no navigation took place
		return nullptr;
	}

	FocusedButton->NavigateFromWidget(NewFocusedButton);
	FocusButton(NewFocusedButton);

	return NewFocusedButton;
}

void UButtonMenuComponent::PressFocusedButton()
{
	if (IsValid(FocusedButton))
	{
		FocusedButton->PressButton();
	}
}

void UButtonMenuComponent::OnMouseCursorOverMenuButton(UProject1ButtonBase* Button)
{
	if (bFocusButtonOnMouseCursorEnter)
	{
		FocusButton(Button);
	}
}

void UButtonMenuComponent::OnMouseCursorLeftMenuButton(UProject1ButtonBase* Button)
{
	if (bUnfocusButtonOnMouseCursorLeave)
	{
		FocusButton(nullptr);
	}
}
