// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuScreenUIInput.h"
#include "EnhancedInputComponent.h"

void UMainMenuScreenUIInput::SetupInput(TObjectPtr<UEnhancedInputComponent> InputComponent)
{
	InputComponent->BindAction(ConfirmInputAction, ETriggerEvent::Triggered, this, &UMainMenuScreenUIInput::OnConfirmTriggered);
	InputComponent->BindAction(NavigateInputAction, ETriggerEvent::Triggered,	this, &UMainMenuScreenUIInput::OnNavigateTriggered);
}

TObjectPtr<UInputMappingContext> UMainMenuScreenUIInput::GetInputMappingContext() const
{
	return InputMappingContext;
}

int32 UMainMenuScreenUIInput::GetInputPriority() const
{
	return InputPriority;
}

void UMainMenuScreenUIInput::OnConfirmTriggered(const FInputActionValue& Value)
{
	ConfirmTriggered.Broadcast(Value);
}

void UMainMenuScreenUIInput::OnNavigateTriggered(const FInputActionValue& Value)
{
	NavigateTriggered.Broadcast(Value);
}
