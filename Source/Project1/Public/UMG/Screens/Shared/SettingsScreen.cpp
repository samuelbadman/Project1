// Fill out your copyright notice in the Description page of Project Settings.


#include "SettingsScreen.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerControllers/Project1PlayerControllerBase.h"
#include "HUDs/Project1HUDBase.h"
#include "Objects/UserWidgetComponents/ButtonMenuComponent.h"
#include "InputActionValue.h"

USettingsScreen::USettingsScreen()
	: Project1PlayerController(nullptr),
	CancelInputDelegateHandle({})
{
	TabButtonMenuComponent = CreateDefaultSubobject<UButtonMenuComponent>(FName(TEXT("ButtonMenuComponent")));
}

void USettingsScreen::NativeOnPushedToLayerStack()
{
	Project1PlayerController = CastChecked<AProject1PlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));

	TabInputDelegateHandle = Project1PlayerController->SettingsScreenTabTriggeredDelegate.AddUObject(this, &USettingsScreen::OnTabInput);
	CancelInputDelegateHandle = Project1PlayerController->SettingsScreenCancelTriggeredDelegate.AddUObject(this, &USettingsScreen::OnCancelInput);

	Project1PlayerController->AddSettingsScreenInputMappingContext();
}

void USettingsScreen::NativeOnPoppedFromLayerStack()
{
	Project1PlayerController->SettingsScreenTabTriggeredDelegate.Remove(TabInputDelegateHandle);
	TabInputDelegateHandle.Reset();

	Project1PlayerController->SettingsScreenCancelTriggeredDelegate.Remove(CancelInputDelegateHandle);
	CancelInputDelegateHandle.Reset();

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
