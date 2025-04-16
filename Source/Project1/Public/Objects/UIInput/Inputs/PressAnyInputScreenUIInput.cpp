// Fill out your copyright notice in the Description page of Project Settings.


#include "PressAnyInputScreenUIInput.h"
#include "EnhancedInputComponent.h"

void UPressAnyInputScreenUIInput::SetupInput(TObjectPtr<UEnhancedInputComponent> InputComponent)
{
	InputComponent->BindAction(PressAnyInputPromptAnyInputInputAction, ETriggerEvent::Triggered, this,
		&UPressAnyInputScreenUIInput::OnPressAnyInputPromptAnyInputTriggered);
}

TObjectPtr<UInputMappingContext> UPressAnyInputScreenUIInput::GetInputMappingContext() const
{
	return PressAnyInputPromptInputMappingContext;
}

int32 UPressAnyInputScreenUIInput::GetInputPriority() const
{
	return PressAnyInputPromptInputPriority;
}

void UPressAnyInputScreenUIInput::OnPressAnyInputPromptAnyInputTriggered(const FInputActionValue& Value)
{
	AnyInputTriggered.Broadcast(Value);
}
