// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleScreenMainMenuScreen.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerControllers/TitleScreenPlayerController.h"
#include "InputActionValue.h"
#include "UMG/Components/Buttons/Project1ButtonBase.h"
#include "Components/ScrollBox.h"

UTitleScreenMainMenuScreen::UTitleScreenMainMenuScreen()
{

}

void UTitleScreenMainMenuScreen::RegisterMenuButtons(const TArray<UProject1ButtonBase*>& Buttons, int32 DefaultHoveredButtonIndex)
{
	for (const TObjectPtr<UProject1ButtonBase> Button : Buttons)
	{
		Button->OnHovered.AddDynamic(this, &UTitleScreenMainMenuScreen::OnRegisteredMenuButtonHovered);
	}

	if (Buttons.IsValidIndex(DefaultHoveredButtonIndex))
	{
		HoverButton(Buttons[DefaultHoveredButtonIndex]);
	}
}

void UTitleScreenMainMenuScreen::NativeOnPushedToLayerStack()
{
	TitleScreenPlayerController = CastChecked<ATitleScreenPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	TitleScreenPlayerController->AddMainMenuScreenInputMappingContext();

	// Register events
	MainMenuUIConfirmTriggeredDelegateHandle = 
		TitleScreenPlayerController->MainMenuScreenConfirmTriggered.AddUObject(this, &UTitleScreenMainMenuScreen::OnMainMenuScreenConfirmTriggered);
	MainMenuUINavigateTriggeredDelegateHandle =
		TitleScreenPlayerController->MainMenuScreenNavigateTriggered.AddUObject(this, &UTitleScreenMainMenuScreen::OnMainMenuScreenNavigateTriggered);
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
	//if (!ButtonNavigationComponent->IsCurrentHoveredButtonValid())
	//{
	//	return;
	//}

	//// Press the currently hovered button
	//ButtonNavigationComponent->GetCurrentHoveredButton()->PressButton();
}

void UTitleScreenMainMenuScreen::OnMainMenuScreenNavigateTriggered(const FInputActionValue& Value)
{
	//if (!ButtonNavigationComponent->IsCurrentHoveredButtonValid())
	//{
	//	return;
	//}

	//// Only care about vertical navigation as the main menu is a vertical list of buttons
	//const float VerticalInput{ StaticCast<float>(Value.Get<FVector2D>().Y) };

	//if (VerticalInput == 0.0f)
	//{
	//	return;
	//}

	//EWidgetNavigationDirection NavDirection{ (VerticalInput > 0) ? EWidgetNavigationDirection::Up : EWidgetNavigationDirection::Down };

	//const TObjectPtr<UProject1ButtonBase> NavigatedButton{ ButtonNavigationComponent->NavigateButton(NavDirection) };
	//if (IsValid(NavigatedButton))
	//{
	//	HoverButton(NavigatedButton);
	//}
}

void UTitleScreenMainMenuScreen::OnRegisteredMenuButtonHovered(UProject1ButtonBase* ButtonHovered)
{


	// Button has hovered itself from mouse cursor interaction so update currently hovered button in button navigation component without hovering the button again
	//ButtonNavigationComponent->SetCurrentHoveredButton(ButtonHovered, false);
}

void UTitleScreenMainMenuScreen::HoverButton(TObjectPtr<UProject1ButtonBase> Button)
{
	//ButtonNavigationComponent->SetCurrentHoveredButton(Button);

	// Scroll to widget in main menu scroll box
	//GetScrollBox()->ScrollWidgetIntoView(Button);
}
