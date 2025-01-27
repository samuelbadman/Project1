// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleScreenMainMenuScreen.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerControllers/TitleScreenPlayerController.h"
#include "InputActionValue.h"
#include "UMG/Components/Buttons/Project1ButtonBase.h"

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
	TitleScreenPlayerController->AddMainMenuUIInputMappingContext();

	// Register events
	MainMenuUIConfirmTriggeredDelegateHandle = TitleScreenPlayerController->MainMenuUIConfirmTriggered.AddUObject(this, &UTitleScreenMainMenuScreen::OnMainMenuUIConfirmTriggered);
	MainMenuUINavigateTriggeredDelegateHandle = TitleScreenPlayerController->MainMenuUINavigateTriggered.AddUObject(this, &UTitleScreenMainMenuScreen::OnMainMenuUINavigateTriggered);
}

void UTitleScreenMainMenuScreen::NativeOnPoppedFromLayerStack()
{
	TitleScreenPlayerController->RemoveMainMenuUIInputMappingContext();

	// Unregister events
	TitleScreenPlayerController->MainMenuUIConfirmTriggered.Remove(MainMenuUIConfirmTriggeredDelegateHandle);
	MainMenuUIConfirmTriggeredDelegateHandle.Reset();

	TitleScreenPlayerController->MainMenuUINavigateTriggered.Remove(MainMenuUINavigateTriggeredDelegateHandle);
	MainMenuUINavigateTriggeredDelegateHandle.Reset();
}

void UTitleScreenMainMenuScreen::OnMainMenuUIConfirmTriggered(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::White, FString::Printf(TEXT("Main menu UI confirm triggered")));
}

void UTitleScreenMainMenuScreen::OnMainMenuUINavigateTriggered(const FInputActionValue& Value)
{
	if (!IsValid(CurrentHoveredButton))
	{
		return;
	}

	// Only care about vertical navigation as the main menu is a vertical list of buttons
	EUINavigation Nav{ (Value.Get<FVector2D>().Y > 0) ? EUINavigation::Up : EUINavigation::Down };

	// Get the button to navigate to. Navigation object is only created when navigation settings are set so can be null
	const TObjectPtr<UWidgetNavigation> WidgetNavigation{ CurrentHoveredButton->Navigation };
	if (!IsValid(WidgetNavigation))
	{
		return;
	}

	// Main menu is expected to be built with extended buttons so the widget being navigated to must be an extended button
	const TObjectPtr<UProject1ButtonBase> NavButton{ Cast<UProject1ButtonBase>(WidgetNavigation->GetNavigationData(Nav).Widget.Get()) };
	if (IsValid(NavButton))
	{
		HoverButton(NavButton);
	}
}

void UTitleScreenMainMenuScreen::OnRegisteredMenuButtonHovered(UProject1ButtonBase* ButtonHovered)
{
	SetHoveredButton(ButtonHovered);
}

void UTitleScreenMainMenuScreen::HoverButton(TObjectPtr<UProject1ButtonBase> Button)
{
	Button->MakeHovered();
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
