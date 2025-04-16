#include "SettingsScreenUIInput.h"
#include "EnhancedInputComponent.h"

void USettingsScreenUIInput::SetupInput(TObjectPtr<UEnhancedInputComponent> InputComponent)
{
	InputComponent->BindAction(TabInputAction, ETriggerEvent::Triggered, this, &USettingsScreenUIInput::OnTabTriggered);
	InputComponent->BindAction(CancelInputAction, ETriggerEvent::Triggered, this, &USettingsScreenUIInput::OnCancelTriggered);
	InputComponent->BindAction(NavigateInputAction, ETriggerEvent::Triggered, this, &USettingsScreenUIInput::OnNavigateTriggered);
	InputComponent->BindAction(ConfirmInputAction, ETriggerEvent::Triggered, this, &USettingsScreenUIInput::OnConfirmTriggered);
}

void USettingsScreenUIInput::OnTabTriggered(const FInputActionValue& Value)
{
	TabTriggeredDelegate.Broadcast(Value);
}

void USettingsScreenUIInput::OnCancelTriggered(const FInputActionValue& Value)
{
	CancelTriggeredDelegate.Broadcast(Value);
}

void USettingsScreenUIInput::OnNavigateTriggered(const FInputActionValue& Value)
{
	NavigateTriggeredDelegate.Broadcast(Value);
}

void USettingsScreenUIInput::OnConfirmTriggered(const FInputActionValue& Value)
{
	ConfirmTriggeredDelegate.Broadcast(Value);
}
