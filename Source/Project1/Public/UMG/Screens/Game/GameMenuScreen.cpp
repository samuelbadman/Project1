// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMenuScreen.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerControllers/GamePlayerController.h"
#include "HUDs/GameHUD.h"
#include "InputActionValue.h"
#include "UMG/Components/Buttons/Project1ButtonBase.h"
#include "Objects/UserWidgetComponents/ButtonMenuComponent.h"

UGameMenuScreen::UGameMenuScreen()
	: GamePlayerController(nullptr),
	GameHUD(nullptr),
	ConfirmDelegateHandle({}),
	NavigateDelegateHandle({}),
	CancelDelegateHandle({})
{
	ButtonMenuComponent = CreateDefaultSubobject<UButtonMenuComponent>(FName(TEXT("ButtonMenuComponent")));
}

void UGameMenuScreen::NativeOnPushedToLayerStack()
{
	GamePlayerController = CastChecked<AGamePlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	GameHUD = CastChecked<AGameHUD>(GamePlayerController->GetHUD());

	AddScreenInputBindings();
	GameHUD->SetGameHUDScreenShown(false);
}

void UGameMenuScreen::NativeOnPoppedFromLayerStack()
{
	RemoveScreenInputBindings();
	GameHUD->SetGameHUDScreenShown(true);
}

void UGameMenuScreen::NativeOnShown()
{
	AddScreenInputBindings();
}

void UGameMenuScreen::NativeOnCollapsed()
{
	RemoveScreenInputBindings();
}

void UGameMenuScreen::OnQuitTriggered(const FInputActionValue& Value)
{
	if (CanReceiveInput())
	{
		GameHUD->CloseGameMenu();
	}
}

void UGameMenuScreen::OnConfirmTriggered(const FInputActionValue& Value)
{
	if (CanReceiveInput())
	{
		ButtonMenuComponent->PressFocusedButton();
	}
}

void UGameMenuScreen::OnNavigateTriggered(const FInputActionValue& Value)
{
	if (CanReceiveInput())
	{
		ButtonMenuComponent->OnNavigationInput((Value.Get<FVector2D>().Y > 0.0f) ? EWidgetNavigationDirection::Up : EWidgetNavigationDirection::Down);
	}
}

void UGameMenuScreen::OnCancelTriggered(const FInputActionValue& Value)
{
	if (CanReceiveInput())
	{
		GameHUD->CloseGameMenu();
	}
}

void UGameMenuScreen::AddScreenInputBindings()
{
	QuitDelegateHandle = GamePlayerController->GameMenuScreenQuitTriggered.AddUObject(this, &UGameMenuScreen::OnQuitTriggered);
	ConfirmDelegateHandle = GamePlayerController->GameMenuScreenConfirmTriggered.AddUObject(this, &UGameMenuScreen::OnConfirmTriggered);
	NavigateDelegateHandle = GamePlayerController->GameMenuScreenNavigateTriggered.AddUObject(this, &UGameMenuScreen::OnNavigateTriggered);
	CancelDelegateHandle = GamePlayerController->GameMenuScreenCancelTriggered.AddUObject(this, &UGameMenuScreen::OnCancelTriggered);

	GamePlayerController->AddGameMenuInputMappingContext();
}

void UGameMenuScreen::RemoveScreenInputBindings()
{
	GamePlayerController->GameMenuScreenQuitTriggered.Remove(QuitDelegateHandle);
	QuitDelegateHandle.Reset();
	GamePlayerController->GameMenuScreenConfirmTriggered.Remove(ConfirmDelegateHandle);
	ConfirmDelegateHandle.Reset();
	GamePlayerController->GameMenuScreenNavigateTriggered.Remove(NavigateDelegateHandle);
	NavigateDelegateHandle.Reset();
	GamePlayerController->GameMenuScreenCancelTriggered.Remove(CancelDelegateHandle);
	CancelDelegateHandle.Reset();

	GamePlayerController->RemoveGameMenuInputMappingContext();
}
