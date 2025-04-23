// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveLoadScreenUIInput.h"
#include "EnhancedInputComponent.h"

USaveLoadScreenUIInput::USaveLoadScreenUIInput()
	: 
	OnCancelInputTriggeredDelegate({}),
	CancelInputAction(nullptr)
{
}

void USaveLoadScreenUIInput::SetupInput(TObjectPtr<UEnhancedInputComponent> InputComponent)
{
	Super::SetupInput(InputComponent);

	InputComponent->BindAction(CancelInputAction, ETriggerEvent::Triggered, this, &USaveLoadScreenUIInput::OnCancelInputTriggered);
}

void USaveLoadScreenUIInput::OnCancelInputTriggered(const FInputActionValue& Value)
{
	OnCancelInputTriggeredDelegate.Broadcast(Value);
}
