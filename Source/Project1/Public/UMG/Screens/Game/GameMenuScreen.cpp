// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMenuScreen.h"
#include "Kismet/GameplayStatics.h"
#include "Controllers/PlayerControllers/Project1PlayerControllerBase.h"
#include "HUDs/GameHUD.h"
#include "InputActionValue.h"
#include "UMG/Components/Buttons/Project1ButtonBase.h"
#include "Objects/UserWidgetComponents/ButtonMenuComponent.h"
#include "GameModes/GameGameMode.h"
#include "Components/TextBlock.h"
#include "Components/ActorComponents/UIInputComponent.h"
#include "Objects/UIInput/Inputs/GameMenuScreenUIInput.h"

UGameMenuScreen::UGameMenuScreen()
	: UIInputKey({}),
	ButtonMenuComponent(CreateDefaultSubobject<UButtonMenuComponent>(FName(TEXT("ButtonMenuComponent")))),
	PlayerController(nullptr),
	GameMenuScreenUIInput(nullptr),
	GameHUD(nullptr),
	GameGameMode(nullptr),
	TotalPlayTimeChangedDelegateHandle({}),
	ConfirmDelegateHandle({}),
	NavigateDelegateHandle({}),
	CancelDelegateHandle({})
{
}

void UGameMenuScreen::NativeOnPushedToLayerStack()
{
	PlayerController = CastChecked<AProject1PlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));
	GameMenuScreenUIInput = PlayerController->GetUIInputComponent()->GetUIInputAs<UGameMenuScreenUIInput>(UIInputKey);
	GameHUD = CastChecked<AGameHUD>(PlayerController->GetHUD());
	GameGameMode = CastChecked<AGameGameMode>(UGameplayStatics::GetGameMode(this));

	// Display current total play time text
	UpdateTotalPlayTimeText();

	// Bind to game second elapsed event in game mode
	TotalPlayTimeChangedDelegateHandle = GameGameMode->OnTotalPlayTimeChanged.AddUObject(this, &UGameMenuScreen::OnTotalPlayTimeChanged);

	AddScreenInputBindings();
	GameHUD->SetGameHUDScreenShown(false);
}

void UGameMenuScreen::NativeOnPoppedFromLayerStack()
{
	GameGameMode->OnTotalPlayTimeChanged.Remove(TotalPlayTimeChangedDelegateHandle);
	TotalPlayTimeChangedDelegateHandle.Reset();

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
		ButtonMenuComponent->NavigateMenu((Value.Get<FVector2D>().Y > 0.0f) ? EWidgetNavigationDirection::Up : EWidgetNavigationDirection::Down);
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
	QuitDelegateHandle = GameMenuScreenUIInput->QuitTriggered.AddUObject(this, &UGameMenuScreen::OnQuitTriggered);
	ConfirmDelegateHandle = GameMenuScreenUIInput->ConfirmTriggered.AddUObject(this, &UGameMenuScreen::OnConfirmTriggered);
	NavigateDelegateHandle = GameMenuScreenUIInput->NavigateTriggered.AddUObject(this, &UGameMenuScreen::OnNavigateTriggered);
	CancelDelegateHandle = GameMenuScreenUIInput->CancelTriggered.AddUObject(this, &UGameMenuScreen::OnCancelTriggered);

	GameMenuScreenUIInput->Add(PlayerController->GetEnhancedInputLocalPlayerSubsystem());
}

void UGameMenuScreen::RemoveScreenInputBindings()
{
	GameMenuScreenUIInput->QuitTriggered.Remove(QuitDelegateHandle);
	QuitDelegateHandle.Reset();

	GameMenuScreenUIInput->ConfirmTriggered.Remove(ConfirmDelegateHandle);
	ConfirmDelegateHandle.Reset();

	GameMenuScreenUIInput->NavigateTriggered.Remove(NavigateDelegateHandle);
	NavigateDelegateHandle.Reset();

	GameMenuScreenUIInput->CancelTriggered.Remove(CancelDelegateHandle);
	CancelDelegateHandle.Reset();

	GameMenuScreenUIInput->Remove(PlayerController->GetEnhancedInputLocalPlayerSubsystem());
}

void UGameMenuScreen::OnTotalPlayTimeChanged(const FPlayTime& NewPlayTime)
{
	UpdateTotalPlayTimeText();
}

void UGameMenuScreen::UpdateTotalPlayTimeText()
{
	const TObjectPtr<UTextBlock> TotalPlayTimeTextBlock{ GetTotalPlayTimeTextBlock() };
	const FPlayTime& TotalPlayTime{ GameGameMode->GetTotalPlayTime() };

	// Update text in widget
	TotalPlayTimeTextBlock->SetText(FText::FromString(TotalPlayTime.ToString()));
}
