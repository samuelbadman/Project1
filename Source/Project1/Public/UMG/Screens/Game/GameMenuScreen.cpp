// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMenuScreen.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerControllers/GamePlayerController.h"
#include "HUDs/GameHUD.h"
#include "Objects/WidgetComponents/ButtonNavigationComponent.h"
#include "InputActionValue.h"
#include "UMG/Components/Buttons/Project1ButtonBase.h"

UGameMenuScreen::UGameMenuScreen()
{
	ButtonNavigationComponent = CreateDefaultSubobject<UButtonNavigationComponent>(FName(TEXT("ButtonNavigationComponent")));
	GamePlayerController = nullptr;
	GameHUD = nullptr;
	ConfirmDelegateHandle = {};
	NavigateDelegateHandle = {};
	CancelDelegateHandle = {};
}

void UGameMenuScreen::RegisterMenuButtons(const TArray<UProject1ButtonBase*>& Buttons, int32 DefaultHoveredButtonIndex)
{
	if (Buttons.IsValidIndex(DefaultHoveredButtonIndex))
	{
		ButtonNavigationComponent->SetCurrentHoveredButton(Buttons[DefaultHoveredButtonIndex]);
	}
}

void UGameMenuScreen::NativeOnPushedToLayerStack()
{
	GamePlayerController = CastChecked<AGamePlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	GameHUD = CastChecked<AGameHUD>(GamePlayerController->GetHUD());
	QuitDelegateHandle = GamePlayerController->GameMenuScreenQuitTriggered.AddUObject(this, &UGameMenuScreen::OnQuitTriggered);
	ConfirmDelegateHandle = GamePlayerController->GameMenuScreenConfirmTriggered.AddUObject(this, &UGameMenuScreen::OnConfirmTriggered);
	NavigateDelegateHandle = GamePlayerController->GameMenuScreenNavigateTriggered.AddUObject(this, &UGameMenuScreen::OnNavigateTriggered);
	CancelDelegateHandle = GamePlayerController->GameMenuScreenCancelTriggered.AddUObject(this, &UGameMenuScreen::OnCancelTriggered);
	GamePlayerController->AddGameMenuInputMappingContext();
}

void UGameMenuScreen::NativeOnPoppedFromLayerStack()
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

void UGameMenuScreen::OnQuitTriggered(const FInputActionValue& Value)
{
	GameHUD->CloseGameMenu();
}

void UGameMenuScreen::OnConfirmTriggered(const FInputActionValue& Value)
{
	ButtonNavigationComponent->GetCurrentHoveredButton()->PressButton();
}

void UGameMenuScreen::OnNavigateTriggered(const FInputActionValue& Value)
{
	const TObjectPtr<UProject1ButtonBase> NavigatedButton{ 
		ButtonNavigationComponent->NavigateButton((Value.Get<FVector2D>().Y > 0.0f) ? EWidgetNavigationDirection::Up : EWidgetNavigationDirection::Down) };
	if (IsValid(NavigatedButton))
	{
		ButtonNavigationComponent->SetCurrentHoveredButton(NavigatedButton);
	}
}

void UGameMenuScreen::OnCancelTriggered(const FInputActionValue& Value)
{
	GameHUD->CloseGameMenu();
}
