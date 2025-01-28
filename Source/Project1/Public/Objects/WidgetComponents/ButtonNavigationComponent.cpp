// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonNavigationComponent.h"
#include "UMG/Components/Buttons/Project1ButtonBase.h"

void UButtonNavigationComponent::SetCurrentHoveredButton(TObjectPtr<UProject1ButtonBase> NewHoveredButton, bool MakeNewHoveredButtonHovered)
{
	if (MakeNewHoveredButtonHovered)
	{
		NewHoveredButton->MakeHovered();
	}

	if (NewHoveredButton != CurrentHoveredButton)
	{
		if (IsValid(CurrentHoveredButton))
		{
			CurrentHoveredButton->MakeUnhovered();
		}
	}

	CurrentHoveredButton = NewHoveredButton;
}

TObjectPtr<UProject1ButtonBase> UButtonNavigationComponent::NavigateButton(EWidgetNavigationDirection Direction)
{
	if (!IsValid(CurrentHoveredButton))
	{
		return nullptr;
	}

	// Get the button to navigate to
	return Cast<UProject1ButtonBase>(CurrentHoveredButton->GetNavigatedWidget(Direction).Get());
}

bool UButtonNavigationComponent::IsCurrentHoveredButtonValid() const
{
	return IsValid(CurrentHoveredButton);
}
