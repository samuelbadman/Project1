// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleScreenMainMenuScreen.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerControllers/TitleScreenPlayerController.h"
#include "InputActionValue.h"
#include "Components/ScrollBox.h"
#include "Objects/UserWidgetComponents/ButtonMenuComponent.h"

UTitleScreenMainMenuScreen::UTitleScreenMainMenuScreen()
{
	ButtonMenuComponent = CreateDefaultSubobject<UButtonMenuComponent>(FName(TEXT("ButtonMenuComponent")));
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
	if (CanReceiveInput())
	{
		ButtonMenuComponent->PressFocusedButton();
	}
}

void UTitleScreenMainMenuScreen::OnMainMenuScreenNavigateTriggered(const FInputActionValue& Value)
{
	if (CanReceiveInput())
	{
		// Only care about vertical navigation as the main menu is a vertical list of buttons
		const float VerticalInput{ StaticCast<float>(Value.Get<FVector2D>().Y) };

		if (VerticalInput == 0.0f)
		{
			return;
		}

		const EWidgetNavigationDirection NavDirection{ (VerticalInput > 0) ? EWidgetNavigationDirection::Up : EWidgetNavigationDirection::Down };
		GetScrollBox()->ScrollWidgetIntoView(StaticCast<UWidget*>(ButtonMenuComponent->NavigateMenu(NavDirection)));
	}
}
