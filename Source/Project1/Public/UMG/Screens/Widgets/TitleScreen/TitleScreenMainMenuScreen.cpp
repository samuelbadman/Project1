// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleScreenMainMenuScreen.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerControllers/TitleScreenPlayerController.h"
#include "InputActionValue.h"
#include "UMG/Components/Buttons/Project1ButtonBase.h"
#include "Components/ScrollBox.h"

void UTitleScreenMainMenuScreen::RegisterMenuButtons(const TArray<UProject1ButtonBase*>& Buttons, int32 DefaultHoveredButtonIndex)
{
	for (const TObjectPtr<UProject1ButtonBase> Button : Buttons)
	{
		Button->OnHovered.AddDynamic(this, &UTitleScreenMainMenuScreen::OnRegisteredMenuButtonHovered);
		Button->SetCanMouseUnhoverButton(false);
	}

	if(Buttons.IsValidIndex(DefaultHoveredButtonIndex))
	{
		HoverButton(Buttons[DefaultHoveredButtonIndex]);
	}
}

void UTitleScreenMainMenuScreen::NativeOnPushedToLayerStack()
{
	TitleScreenPlayerController = CastChecked<ATitleScreenPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	TitleScreenPlayerController->AddMainMenuScreenInputMappingContext();

	// Register events
	MainMenuUIConfirmTriggeredDelegateHandle = TitleScreenPlayerController->MainMenuScreenConfirmTriggered.AddUObject(this, &UTitleScreenMainMenuScreen::OnMainMenuScreenConfirmTriggered);
	MainMenuUINavigateTriggeredDelegateHandle = TitleScreenPlayerController->MainMenuScreenNavigateTriggered.AddUObject(this, &UTitleScreenMainMenuScreen::OnMainMenuScreenNavigateTriggered);
}

void UTitleScreenMainMenuScreen::NativeOnPoppedFromLayerStack()
{
	TitleScreenPlayerController->RemoveMainMenuScreenInputMappingContext();

	// Unregister events
	TitleScreenPlayerController->MainMenuScreenConfirmTriggered.Remove(MainMenuUIConfirmTriggeredDelegateHandle);
	MainMenuUIConfirmTriggeredDelegateHandle.Reset();

	TitleScreenPlayerController->MainMenuScreenNavigateTriggered.Remove(MainMenuUINavigateTriggeredDelegateHandle);
	MainMenuUINavigateTriggeredDelegateHandle.Reset();
}

void UTitleScreenMainMenuScreen::OnMainMenuScreenConfirmTriggered(const FInputActionValue& Value)
{
	if (!IsValid(CurrentHoveredButton))
	{
		return;
	}

	// Press the currently hovered button
	CurrentHoveredButton->PressButton();
}

void UTitleScreenMainMenuScreen::OnMainMenuScreenNavigateTriggered(const FInputActionValue& Value)
{
	if (!IsValid(CurrentHoveredButton))
	{
		return;
	}

	// Only care about vertical navigation as the main menu is a vertical list of buttons
	const float VerticalInput{ StaticCast<float>(Value.Get<FVector2D>().Y) };

	if (VerticalInput == 0.0f)
	{
		return;
	}

	EWidgetNavigationDirection NavDirection{ (VerticalInput > 0) ? EWidgetNavigationDirection::Up : EWidgetNavigationDirection::Down };

	// Get the button to navigate to. Navigated widgets in the main menu should be buttons
	const TObjectPtr<UProject1ButtonBase> NavigatedButton{ Cast<UProject1ButtonBase>(CurrentHoveredButton->GetNavigatedWidget(NavDirection).Get()) };

	// Hover the button if it is valid
	if (IsValid(NavigatedButton))
	{
		HoverButton(NavigatedButton);
	}
}

void UTitleScreenMainMenuScreen::OnRegisteredMenuButtonHovered(UProject1ButtonBase* ButtonHovered)
{
	SetHoveredButton(ButtonHovered);
}

void UTitleScreenMainMenuScreen::HoverButton(TObjectPtr<UProject1ButtonBase> Button)
{
	Button->MakeHovered();

	// Scroll to widget in main menu scroll box
	GetScrollBox()->ScrollWidgetIntoView(Button);
}

void UTitleScreenMainMenuScreen::SetHoveredButton(TObjectPtr<UProject1ButtonBase> NewHoveredButton)
{
	if (NewHoveredButton != CurrentHoveredButton)
	{
		if (IsValid(CurrentHoveredButton))
		{
			CurrentHoveredButton->MakeUnhovered();
		}
	}

	CurrentHoveredButton = NewHoveredButton;
}
