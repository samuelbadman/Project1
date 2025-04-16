#include "ConfirmModalScreenUIInput.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

void UConfirmModalScreenUIInput::SetupInput(TObjectPtr<UEnhancedInputComponent> InputComponent)
{
	InputComponent->BindAction(ConfirmInputAction, ETriggerEvent::Triggered, this, &UConfirmModalScreenUIInput::OnConfirmTriggered);
	InputComponent->BindAction(NavigateInputAction, ETriggerEvent::Triggered, this, &UConfirmModalScreenUIInput::OnNavigateTriggered);
}

void UConfirmModalScreenUIInput::OnConfirmTriggered(const FInputActionValue& Value)
{
	ConfirmTriggeredDelegate.Broadcast(Value);
}

void UConfirmModalScreenUIInput::OnNavigateTriggered(const FInputActionValue& Value)
{
	NavigateTriggeredDelegate.Broadcast(Value);
}
