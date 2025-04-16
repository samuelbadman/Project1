// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractPromptScreenUIInput.h"
#include "EnhancedInputComponent.h"

void UInteractPromptScreenUIInput::SetupInput(TObjectPtr<UEnhancedInputComponent> InputComponent)
{
	InputComponent->BindAction(InteractInputAction, ETriggerEvent::Triggered, this, &UInteractPromptScreenUIInput::OnInteractTriggered);
	InputComponent->BindAction(SwitchActionInputAction, ETriggerEvent::Triggered, this, &UInteractPromptScreenUIInput::OnSwitchActionTriggered);
}

TObjectPtr<UInputMappingContext> UInteractPromptScreenUIInput::GetInputMappingContext() const
{
	return InputMappingContext;
}

int32 UInteractPromptScreenUIInput::GetInputPriority() const
{
	return InputPriority;
}

void UInteractPromptScreenUIInput::OnInteractTriggered(const FInputActionValue& Value)
{
	InteractTriggered.Broadcast(Value);
}

void UInteractPromptScreenUIInput::OnSwitchActionTriggered(const FInputActionValue& Value)
{
	SwitchActionTriggered.Broadcast(Value);
}
