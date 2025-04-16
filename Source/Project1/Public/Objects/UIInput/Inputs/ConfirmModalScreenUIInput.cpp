#include "ConfirmModalScreenUIInput.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

void UConfirmModalScreenUIInput::SetupInput(TObjectPtr<UEnhancedInputComponent> InputComponent)
{
	InputComponent->BindAction(ConfirmInputAction, ETriggerEvent::Triggered, this, &UConfirmModalScreenUIInput::OnConfirmTriggered);
	InputComponent->BindAction(NavigateInputAction, ETriggerEvent::Triggered, this, &UConfirmModalScreenUIInput::OnNavigateTriggered);
}

TObjectPtr<UInputMappingContext> UConfirmModalScreenUIInput::GetInputMappingContext() const
{
	return InputMappingContext;
}

int32 UConfirmModalScreenUIInput::GetInputPriority() const
{
	return InputPriority;
}

void UConfirmModalScreenUIInput::OnConfirmTriggered(const FInputActionValue& Value)
{
	ConfirmTriggeredDelegate.Broadcast(Value);
}

void UConfirmModalScreenUIInput::OnNavigateTriggered(const FInputActionValue& Value)
{
	NavigateTriggeredDelegate.Broadcast(Value);
}
