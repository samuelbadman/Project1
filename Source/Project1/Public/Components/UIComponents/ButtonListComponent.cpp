// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonListComponent.h"
#include "UserWidgets/ComponentWidgets/Buttons/Project1ButtonWidgetBase.h"
#include "FunctionLibraries/Project1BlueprintFunctionLibrary.h"

void UButtonListComponent::RegisterButtons(const TArray<UProject1ButtonWidgetBase*>& Buttons, int32 NewActiveButtonIndex)
{
	RegisteredButtons = Buttons;

	for (TObjectPtr<UProject1ButtonWidgetBase> Button : Buttons)
	{
		Button->GetOnMouseEnteredGeometryDelegate().AddDynamic(this, &UButtonListComponent::OnMouseEnteredRegisteredButtonGeometry);
	}

	SetActiveButtonIndex(NewActiveButtonIndex);
}

void UButtonListComponent::Navigate(int32 Value, bool Wrap)
{
	// Ignore navigation input if there are no buttons registered
	if (RegisteredButtons.Num() == 0)
	{
		return;
	}

	if (Wrap)
	{
		SetActiveButtonIndex(UProject1BlueprintFunctionLibrary::WrapIncrementArrayIndex(
			ActiveButtonIndex,
			RegisteredButtons.Num(),
			Value
		));
	}
	else
	{
		SetActiveButtonIndex(FMath::Clamp(ActiveButtonIndex + Value, 0, RegisteredButtons.Num() - 1));
	}
}

void UButtonListComponent::PressActiveButton()
{
	if (!RegisteredButtons.IsValidIndex(ActiveButtonIndex))
	{
		return;
	}

	RegisteredButtons[ActiveButtonIndex]->Press();
}

void UButtonListComponent::PressActiveButtonIfUnderMouse()
{
	if (IsActiveButtonUnderMouse())
	{
		PressActiveButton();
	}
}

bool UButtonListComponent::IsActiveButtonUnderMouse() const
{
	const TObjectPtr<UProject1ButtonWidgetBase> ActiveButton{ GetActiveButton() };
	return (IsValid(ActiveButton)) ? ActiveButton->IsUnderMouse() : false;
}

void UButtonListComponent::ActivateButton(int32 ButtonIndex)
{
	if (!RegisteredButtons.IsValidIndex(ButtonIndex))
	{
		return;
	}

	RegisteredButtons[ButtonIndex]->MakeActive();
}

void UButtonListComponent::DeactivateButton(int32 ButtonIndex)
{
	if (!RegisteredButtons.IsValidIndex(ButtonIndex))
	{
		return;
	}

	RegisteredButtons[ButtonIndex]->EndActive();
}

void UButtonListComponent::SetActiveButtonIndex(int32 NewActiveButtonIndex)
{
	if (ActiveButtonIndex == NewActiveButtonIndex)
	{
		return;
	}

	if (!RegisteredButtons.IsValidIndex(NewActiveButtonIndex))
	{
		return;
	}

	// Deactivate current active button. Current active button index may not be valid so only do this if it is
	if (RegisteredButtons.IsValidIndex(ActiveButtonIndex))
	{
		DeactivateButton(ActiveButtonIndex);
	}

	// Update index
	ActiveButtonIndex = NewActiveButtonIndex;

	// Activate button at new active button index
	ActivateButton(NewActiveButtonIndex);
}

TObjectPtr<UProject1ButtonWidgetBase> UButtonListComponent::GetActiveButton() const
{
	return (RegisteredButtons.IsValidIndex(ActiveButtonIndex)) ? RegisteredButtons[ActiveButtonIndex] : nullptr;
}

void UButtonListComponent::OnMouseEnteredRegisteredButtonGeometry(UProject1ButtonWidgetBase* Button)
{
	SetActiveButtonIndex(RegisteredButtons.Find(Button));
}
