// Fill out your copyright notice in the Description page of Project Settings.


#include "SettingsScreen.h"
#include "Kismet/GameplayStatics.h"
#include "Controllers/PlayerControllers/Project1PlayerControllerBase.h"
#include "Objects/UserWidgetComponents/ButtonMenuComponent.h"
#include "InputActionValue.h"
#include "UMG/Components/Settings/SettingsPageWidget.h"
#include "Objects/UIInput/Inputs/SettingsScreenUIInput.h"
#include "Components/ActorComponents/UIInputComponent.h"

USettingsScreen::USettingsScreen()
	: 
	Project1PlayerController(nullptr),
	SettingsScreenUIInput(nullptr),
	TabInputDelegateHandle({}),
	CancelInputDelegateHandle({}),
	NavigateInputDelegateHandle({}),
	CurrentSettingsPage(nullptr)
{
	TabButtonMenuComponent = CreateDefaultSubobject<UButtonMenuComponent>(FName(TEXT("ButtonMenuComponent")));
}

void USettingsScreen::ChangeSettingsPage(USettingsPageWidget* NewPage)
{
	if (IsValid(CurrentSettingsPage))
	{
		CurrentSettingsPage->Collapse();
	}

	CurrentSettingsPage = NewPage;
	NewPage->Show();
}

void USettingsScreen::NativeOnPushedToLayerStack()
{
	Project1PlayerController = CastChecked<AProject1PlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));
	SettingsScreenUIInput = Project1PlayerController->GetUIInputComponent()->GetUIInputAs<USettingsScreenUIInput>(UIInputKey);

	TabInputDelegateHandle = SettingsScreenUIInput->TabTriggeredDelegate.AddUObject(this, &USettingsScreen::OnTabInput);
	CancelInputDelegateHandle = SettingsScreenUIInput->CancelTriggeredDelegate.AddUObject(this, &USettingsScreen::OnCancelInput);
	NavigateInputDelegateHandle = SettingsScreenUIInput->NavigateTriggeredDelegate.AddUObject(this, &USettingsScreen::OnNavigateInput);
	NavigateContinuousInputDelegateHandle = SettingsScreenUIInput->NavigateContinuousTriggeredDelegate.AddUObject(this, &USettingsScreen::OnNavigateContinuousInput);
	ConfirmInputDelegateHandle = SettingsScreenUIInput->ConfirmTriggeredDelegate.AddUObject(this, &USettingsScreen::OnConfirmInput);

	SettingsScreenUIInput->Add(Project1PlayerController->GetEnhancedInputLocalPlayerSubsystem());
}

void USettingsScreen::NativeOnPoppedFromLayerStack()
{
	SettingsScreenUIInput->TabTriggeredDelegate.Remove(TabInputDelegateHandle);
	TabInputDelegateHandle.Reset();

	SettingsScreenUIInput->CancelTriggeredDelegate.Remove(CancelInputDelegateHandle);
	CancelInputDelegateHandle.Reset();

	SettingsScreenUIInput->NavigateTriggeredDelegate.Remove(NavigateInputDelegateHandle);
	NavigateInputDelegateHandle.Reset();

	SettingsScreenUIInput->NavigateContinuousTriggeredDelegate.Remove(NavigateContinuousInputDelegateHandle);
	NavigateContinuousInputDelegateHandle.Reset();

	SettingsScreenUIInput->ConfirmTriggeredDelegate.Remove(ConfirmInputDelegateHandle);
	ConfirmInputDelegateHandle.Reset();

	SettingsScreenUIInput->Remove(Project1PlayerController->GetEnhancedInputLocalPlayerSubsystem());
}

void USettingsScreen::OnTabInput(const FInputActionValue& Value)
{
	if (CanReceiveInput())
	{
		TabButtonMenuComponent->NavigateMenu((Value.Get<FVector2D>().X) > 0.0f ? EWidgetNavigationDirection::Right : EWidgetNavigationDirection::Left);
	}
}

void USettingsScreen::OnCancelInput(const FInputActionValue& Value)
{
	if (CanReceiveInput())
	{
		CastChecked<AProject1HUDBase>(Project1PlayerController->GetHUD())->PopContentFromPrimaryLayoutWidgetLayer(GetOwningLayerName());
	}
}

void USettingsScreen::OnNavigateInput(const FInputActionValue& Value)
{
	if (CanReceiveInput())
	{
		if (IsValid(CurrentSettingsPage))
		{
			CurrentSettingsPage->OnNavigationInput(Value.Get<FVector2D>());
		}
	}
}

void USettingsScreen::OnNavigateContinuousInput(const FInputActionValue& Value)
{
	if (CanReceiveInput())
	{
		if (IsValid(CurrentSettingsPage))
		{
			CurrentSettingsPage->OnContinuousNavigationInput(Value.Get<FVector2D>());
		}
	}
}

void USettingsScreen::OnConfirmInput(const FInputActionValue& Value)
{
	if (CanReceiveInput())
	{
		if (IsValid(CurrentSettingsPage))
		{
			CurrentSettingsPage->OnConfirmInput();
		}
	}
}
