// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueScreenUIInput.h"
#include "EnhancedInputComponent.h"

void UDialogueScreenUIInput::SetupInput(TObjectPtr<UEnhancedInputComponent> InputComponent)
{
	InputComponent->BindAction(ConfirmInputAction, ETriggerEvent::Triggered, this, &UDialogueScreenUIInput::OnConfirmTriggered);
}

void UDialogueScreenUIInput::OnConfirmTriggered(const FInputActionValue& Value)
{
	ConfirmTriggered.Broadcast(Value);
}
