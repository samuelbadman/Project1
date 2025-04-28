// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveLoadScreenUIInput.h"
#include "EnhancedInputComponent.h"

USaveLoadScreenUIInput::USaveLoadScreenUIInput()
	: 
	OnCancelInputTriggeredDelegate({}),
	CancelInputAction(nullptr),
	ConfirmInputAction(nullptr),
	NavigateInputAction(nullptr)
{
}

void USaveLoadScreenUIInput::SetupInput(TObjectPtr<UEnhancedInputComponent> InputComponent)
{
	Super::SetupInput(InputComponent);

	InputComponent->BindAction(CancelInputAction, ETriggerEvent::Triggered, this, &USaveLoadScreenUIInput::OnCancelInputTriggered);
	InputComponent->BindAction(ConfirmInputAction, ETriggerEvent::Triggered, this, &USaveLoadScreenUIInput::OnConfirmInputTriggered);
	InputComponent->BindAction(NavigateInputAction, ETriggerEvent::Triggered, this, &USaveLoadScreenUIInput::OnNavigateInputTriggered);
}

void USaveLoadScreenUIInput::OnCancelInputTriggered(const FInputActionValue& Value)
{
	OnCancelInputTriggeredDelegate.Broadcast(Value);
}

void USaveLoadScreenUIInput::OnConfirmInputTriggered(const FInputActionValue& Value)
{
	OnConfirmInputTriggeredDelegate.Broadcast(Value);
}

void USaveLoadScreenUIInput::OnNavigateInputTriggered(const FInputActionValue& Value)
{
	OnNavigateInputTriggeredDelegate.Broadcast(Value);
}
