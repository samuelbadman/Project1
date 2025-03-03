// Fill out your copyright notice in the Description page of Project Settings.


#include "SettingsScreen.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerControllers/Project1PlayerControllerBase.h"
#include "HUDs/Project1HUDBase.h"

USettingsScreen::USettingsScreen()
	: Project1PlayerController(nullptr),
	CancelInputDelegateHandle({})
{
}

void USettingsScreen::NativeOnPushedToLayerStack()
{
	Project1PlayerController = CastChecked<AProject1PlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));

	CancelInputDelegateHandle = Project1PlayerController->SettingsScreenCancelTriggeredDelegate.AddUObject(this, &USettingsScreen::OnCancelInput);

	Project1PlayerController->AddSettingsScreenInputMappingContext();
}

void USettingsScreen::NativeOnPoppedFromLayerStack()
{
	Project1PlayerController->SettingsScreenCancelTriggeredDelegate.Remove(CancelInputDelegateHandle);
	CancelInputDelegateHandle.Reset();

	Project1PlayerController->RemoveSettingsScreenInputMappingContext();
}

void USettingsScreen::OnCancelInput(const FInputActionValue& Value)
{
	if (CanReceiveInput())
	{
		CastChecked<AProject1HUDBase>(Project1PlayerController->GetHUD())->PopContentFromPrimaryLayoutWidgetLayer(GetOwningLayerName());
	}
}
