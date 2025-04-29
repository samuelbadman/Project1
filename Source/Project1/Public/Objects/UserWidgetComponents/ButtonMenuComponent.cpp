// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonMenuComponent.h"
#include "UMG/Components/Buttons/Project1ButtonBase.h"

UButtonMenuComponent::UButtonMenuComponent()
	: bFocusButtonOnMouseCursorEnter(true),
	bUnfocusButtonOnMouseCursorLeave(true),
	RegisteredButtons({}),
	FocusedButton(nullptr)
{
}

void UButtonMenuComponent::RegisterMenuButtons(const TArray<UProject1ButtonBase*>& Buttons, bool ActivateButtonMouseInput)
{
	RegisteredButtons = Buttons;

	for (const TObjectPtr<UProject1ButtonBase>& Button : RegisteredButtons)
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
	if (IsValid(FocusedButton))
	{
		FocusedButton->MakeUnhovered();
	}

	FocusedButton = Button;

	if (!RegisteredButtons.Contains(Button))
	{
		return;
	}

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
