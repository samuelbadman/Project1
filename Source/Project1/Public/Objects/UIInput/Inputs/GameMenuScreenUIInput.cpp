// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMenuScreenUIInput.h"
#include "EnhancedInputComponent.h"

void UGameMenuScreenUIInput::SetupInput(TObjectPtr<UEnhancedInputComponent> InputComponent)
{
	InputComponent->BindAction(ConfirmInputAction, ETriggerEvent::Triggered, this, &UGameMenuScreenUIInput::OnConfirmTriggered);
	InputComponent->BindAction(NavigateInputAction, ETriggerEvent::Triggered, this, &UGameMenuScreenUIInput::OnNavigateTriggered);
	InputComponent->BindAction(CancelInputAction, ETriggerEvent::Triggered, this, &UGameMenuScreenUIInput::OnCancelTriggered);
	InputComponent->BindAction(QuitInputAction, ETriggerEvent::Triggered, this, &UGameMenuScreenUIInput::OnQuitTriggered);
}

void UGameMenuScreenUIInput::OnConfirmTriggered(const FInputActionValue& Value)
{
	ConfirmTriggered.Broadcast(Value);
}

void UGameMenuScreenUIInput::OnNavigateTriggered(const FInputActionValue& Value)
{
	NavigateTriggered.Broadcast(Value);
}

void UGameMenuScreenUIInput::OnCancelTriggered(const FInputActionValue& Value)
{
	CancelTriggered.Broadcast(Value);
}

void UGameMenuScreenUIInput::OnQuitTriggered(const FInputActionValue& Value)
{
	QuitTriggered.Broadcast(Value);
}
