#include "DynamicModalScreenUIInput.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

void UDynamicModalScreenUIInput::SetupInput(TObjectPtr<UEnhancedInputComponent> InputComponent)
{
	InputComponent->BindAction(DynamicModalConfirmInputAction, ETriggerEvent::Triggered, this, &UDynamicModalScreenUIInput::OnDynamicModalConfirmTriggered);
	InputComponent->BindAction(DynamicModalNavigateInputAction, ETriggerEvent::Triggered, this, &UDynamicModalScreenUIInput::OnDynamicModalNavigateTriggered);
}

TObjectPtr<UInputMappingContext> UDynamicModalScreenUIInput::GetInputMappingContext() const
{
	return DynamicModalInputMappingContext;
}

int32 UDynamicModalScreenUIInput::GetInputPriority() const
{
	return DynamicModalInputPriority;
}

void UDynamicModalScreenUIInput::OnDynamicModalConfirmTriggered(const FInputActionValue& Value)
{
	DynamicModalConfirmTriggered.Broadcast(Value);
}

void UDynamicModalScreenUIInput::OnDynamicModalNavigateTriggered(const FInputActionValue& Value)
{
	DynamicModalNavigateTriggered.Broadcast(Value);
}
