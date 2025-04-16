// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueScreenUIInput.h"
#include "EnhancedInputComponent.h"

void UDialogueScreenUIInput::SetupInput(TObjectPtr<UEnhancedInputComponent> InputComponent)
{
	InputComponent->BindAction(ConfirmInputAction, ETriggerEvent::Triggered, this, &UDialogueScreenUIInput::OnConfirmTriggered);
}

TObjectPtr<UInputMappingContext> UDialogueScreenUIInput::GetInputMappingContext() const
{
	return InputMappingContext;
}

int32 UDialogueScreenUIInput::GetInputPriority() const
{
	return InputPriority;
}

void UDialogueScreenUIInput::OnConfirmTriggered(const FInputActionValue& Value)
{
	ConfirmTriggered.Broadcast(Value);
}
