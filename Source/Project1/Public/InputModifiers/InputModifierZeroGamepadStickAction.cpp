// Fill out your copyright notice in the Description page of Project Settings.


#include "InputModifierZeroGamepadStickAction.h"
#include "EnhancedPlayerInput.h"

FInputActionValue UInputModifierZeroGamepadStickAction::ModifyRaw_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue CurrentValue, float DeltaTime)
{
	const TObjectPtr<APlayerController> PlayerController{ PlayerInput->GetOuterAPlayerController() };

	if ((PlayerController->IsInputKeyDown(EKeys::Gamepad_LeftStick_Up)) ||
		(PlayerController->IsInputKeyDown(EKeys::Gamepad_LeftStick_Down)) ||
		(PlayerController->IsInputKeyDown(EKeys::Gamepad_LeftStick_Left)) ||
		(PlayerController->IsInputKeyDown(EKeys::Gamepad_LeftStick_Right)) ||
		(PlayerController->IsInputKeyDown(EKeys::Gamepad_RightStick_Up)) ||
		(PlayerController->IsInputKeyDown(EKeys::Gamepad_RightStick_Down)) ||
		(PlayerController->IsInputKeyDown(EKeys::Gamepad_RightStick_Left)) ||
		(PlayerController->IsInputKeyDown(EKeys::Gamepad_RightStick_Right)))
	{
		return FInputActionValue();
	}

	return CurrentValue;
}
