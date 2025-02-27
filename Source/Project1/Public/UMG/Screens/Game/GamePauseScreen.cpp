// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePauseScreen.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerControllers/GamePlayerController.h"
#include "HUDs/GameHUD.h"
#include "InputActionValue.h"
#include "UMG/Components/Buttons/Project1ButtonBase.h"

UGamePauseScreen::UGamePauseScreen()
{
	GamePlayerController = nullptr;
	GameHUD = nullptr;
	ConfirmDelegateHandle = {};
	NavigateDelegateHandle = {};
	CancelDelegateHandle = {};
}

void UGamePauseScreen::RegisterMenuButtons(const TArray<UProject1ButtonBase*>& Buttons, int32 DefaultHoveredButtonIndex)
{
	//if (Buttons.IsValidIndex(DefaultHoveredButtonIndex))
	//{
	//	ButtonNavigationComponent->SetCurrentHoveredButton(Buttons[DefaultHoveredButtonIndex]);
	//}
}

void UGamePauseScreen::NativeOnPushedToLayerStack()
{
	GamePlayerController = CastChecked<AGamePlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	GameHUD = CastChecked<AGameHUD>(GamePlayerController->GetHUD());

	AddScreenInputBindings();
	GameHUD->SetGameHUDScreenShown(false);
}

void UGamePauseScreen::NativeOnPoppedFromLayerStack()
{
	RemoveScreenInputBindings();
	GameHUD->SetGameHUDScreenShown(true);
}

void UGamePauseScreen::NativeOnShown()
{
	AddScreenInputBindings();
}

void UGamePauseScreen::NativeOnCollapsed()
{
	RemoveScreenInputBindings();
}

void UGamePauseScreen::OnQuitTriggered(const FInputActionValue& Value)
{
	if (CanReceiveInput())
	{
		GameHUD->CloseGameMenu();
	}
}

void UGamePauseScreen::OnConfirmTriggered(const FInputActionValue& Value)
{
	if (CanReceiveInput())
	{

	}
	//ButtonNavigationComponent->GetCurrentHoveredButton()->PressButton();
}

void UGamePauseScreen::OnNavigateTriggered(const FInputActionValue& Value)
{
	if (CanReceiveInput())
	{

	}
	//const TObjectPtr<UProject1ButtonBase> NavigatedButton{ 
	//	ButtonNavigationComponent->NavigateButton((Value.Get<FVector2D>().Y > 0.0f) ? EWidgetNavigationDirection::Up : EWidgetNavigationDirection::Down) };
	//if (IsValid(NavigatedButton))
	//{
	//	ButtonNavigationComponent->SetCurrentHoveredButton(NavigatedButton);
	//}
}

void UGamePauseScreen::OnCancelTriggered(const FInputActionValue& Value)
{
	if (CanReceiveInput())
	{
		GameHUD->CloseGameMenu();
	}
}

void UGamePauseScreen::AddScreenInputBindings()
{
	QuitDelegateHandle = GamePlayerController->GameMenuScreenQuitTriggered.AddUObject(this, &UGamePauseScreen::OnQuitTriggered);
	ConfirmDelegateHandle = GamePlayerController->GameMenuScreenConfirmTriggered.AddUObject(this, &UGamePauseScreen::OnConfirmTriggered);
	NavigateDelegateHandle = GamePlayerController->GameMenuScreenNavigateTriggered.AddUObject(this, &UGamePauseScreen::OnNavigateTriggered);
	CancelDelegateHandle = GamePlayerController->GameMenuScreenCancelTriggered.AddUObject(this, &UGamePauseScreen::OnCancelTriggered);

	GamePlayerController->AddGameMenuInputMappingContext();
}

void UGamePauseScreen::RemoveScreenInputBindings()
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
