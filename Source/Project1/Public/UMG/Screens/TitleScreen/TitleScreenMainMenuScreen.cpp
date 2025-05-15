// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleScreenMainMenuScreen.h"
#include "Kismet/GameplayStatics.h"
#include "Controllers/PlayerControllers/Project1PlayerControllerBase.h"
#include "InputActionValue.h"
#include "Components/ScrollBox.h"
#include "Objects/UserWidgetComponents/ButtonMenuComponent.h"
#include "Components/ActorComponents/UIInputComponent.h"
#include "Objects/UIInput/Inputs/MainMenuScreenUIInput.h"
#include "GameInstances/Project1GameInstanceBase.h"
#include "SaveGame/SaveManager.h"
#include "UMG/Components/Buttons/Project1ButtonBase.h"

UTitleScreenMainMenuScreen::UTitleScreenMainMenuScreen()
{
	ButtonMenuComponent = CreateDefaultSubobject<UButtonMenuComponent>(FName(TEXT("ButtonMenuComponent")));
}

void UTitleScreenMainMenuScreen::NativeOnPushedToLayerStack()
{
	Project1PlayerController = CastChecked<AProject1PlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));
	MainMenuScreenUIInput = Project1PlayerController->GetUIInputComponent()->GetUIInputAs<UMainMenuScreenUIInput>(UIInputKey);

	MainMenuScreenUIInput->Add(Project1PlayerController->GetEnhancedInputLocalPlayerSubsystem());

	// Load meta save game data if present otherwise create a new meta save game.
	const TObjectPtr<USaveManager> SaveManager{ CastChecked<UProject1GameInstanceBase>(UGameplayStatics::GetGameInstance(this))->GetSaveManager() };

	if (SaveManager->IsMetaSaveDataPresent())
	{
		SaveManager->LoadMetaData(false);
	}
	else
	{
		SaveManager->CreateNewMetaSaveGame();
	}

	// Register events
	MainMenuUIConfirmTriggeredDelegateHandle = MainMenuScreenUIInput->ConfirmTriggered.AddUObject(this,
		&UTitleScreenMainMenuScreen::OnConfirmTriggered);
	MainMenuUINavigateTriggeredDelegateHandle = MainMenuScreenUIInput->NavigateTriggered.AddUObject(this, 
		&UTitleScreenMainMenuScreen::OnNavigateTriggered);

	// Check if there is no game save game data present on disk
	if (!SaveManager->IsAnyGameSaveDataPresent())
	{
		// No game save game data present
		GetContinueButton()->SetVisibility(ESlateVisibility::Collapsed);

		const TObjectPtr<UProject1ButtonBase> FirstMenuButton{ GetFirstMenuButtonWithoutContinue() };
		const TObjectPtr<UProject1ButtonBase> LastMenuButton{ GetLastMenuButton() };

		FirstMenuButton->SetNavigationWidget(EWidgetNavigationDirection::Up, LastMenuButton);
		LastMenuButton->SetNavigationWidget(EWidgetNavigationDirection::Down, FirstMenuButton);
	}
	else
	{
		// Game save game data is present
		const TObjectPtr<UProject1ButtonBase> ContinueButton{ GetContinueButton() };
		ButtonMenuComponent->RegisterMenuButtons(TArray<UProject1ButtonBase*>{ ContinueButton }, true);
	}
}

void UTitleScreenMainMenuScreen::NativeOnPoppedFromLayerStack()
{
	MainMenuScreenUIInput->Remove(Project1PlayerController->GetEnhancedInputLocalPlayerSubsystem());

	// Unregister events
	MainMenuScreenUIInput->ConfirmTriggered.Remove(MainMenuUIConfirmTriggeredDelegateHandle);
	MainMenuUIConfirmTriggeredDelegateHandle.Reset();

	MainMenuScreenUIInput->NavigateTriggered.Remove(MainMenuUINavigateTriggeredDelegateHandle);
	MainMenuUINavigateTriggeredDelegateHandle.Reset();
}

void UTitleScreenMainMenuScreen::OnConfirmTriggered(const FInputActionValue& Value)
{
	if (CanReceiveInput())
	{
		ButtonMenuComponent->PressFocusedButton();
	}
}

void UTitleScreenMainMenuScreen::OnNavigateTriggered(const FInputActionValue& Value)
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
