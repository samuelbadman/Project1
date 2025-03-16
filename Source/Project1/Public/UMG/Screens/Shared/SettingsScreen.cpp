// Fill out your copyright notice in the Description page of Project Settings.


#include "SettingsScreen.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerControllers/Project1PlayerControllerBase.h"
#include "HUDs/Project1HUDBase.h"
#include "Objects/UserWidgetComponents/ButtonMenuComponent.h"
#include "InputActionValue.h"
#include "UMG/Components/Settings/SettingsPageWidget.h"

USettingsScreen::USettingsScreen()
	: Project1PlayerController(nullptr),
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

	TabInputDelegateHandle = Project1PlayerController->SettingsScreenTabTriggeredDelegate.AddUObject(this, &USettingsScreen::OnTabInput);
	CancelInputDelegateHandle = Project1PlayerController->SettingsScreenCancelTriggeredDelegate.AddUObject(this, &USettingsScreen::OnCancelInput);
	NavigateInputDelegateHandle = Project1PlayerController->SettingsScreenNavigateTriggeredDelegate.AddUObject(this, &USettingsScreen::OnNavigateInput);
	ConfirmInputDelegateHandle = Project1PlayerController->SettingsScreenConfirmTriggeredDelegate.AddUObject(this, &USettingsScreen::OnConfirmInput);

	Project1PlayerController->AddSettingsScreenInputMappingContext();
}

void USettingsScreen::NativeOnPoppedFromLayerStack()
{
	Project1PlayerController->SettingsScreenTabTriggeredDelegate.Remove(TabInputDelegateHandle);
	TabInputDelegateHandle.Reset();

	Project1PlayerController->SettingsScreenCancelTriggeredDelegate.Remove(CancelInputDelegateHandle);
	CancelInputDelegateHandle.Reset();

	Project1PlayerController->SettingsScreenNavigateTriggeredDelegate.Remove(NavigateInputDelegateHandle);
	NavigateInputDelegateHandle.Reset();

	Project1PlayerController->SettingsScreenConfirmTriggeredDelegate.Remove(ConfirmInputDelegateHandle);
	ConfirmInputDelegateHandle.Reset();

	Project1PlayerController->RemoveSettingsScreenInputMappingContext();
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
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::White, FString::Printf(TEXT("Settings screen navigate input: %s"), *Value.Get<FVector2D>().ToString()));
	}
}

void USettingsScreen::OnConfirmInput(const FInputActionValue& Value)
{
	if (CanReceiveInput())
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::White, FString::Printf(TEXT("Settings screen confirm input")));
	}
}
