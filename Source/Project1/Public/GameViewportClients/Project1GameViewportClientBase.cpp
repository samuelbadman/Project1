// Fill out your copyright notice in the Description page of Project Settings.


#include "Project1GameViewportClientBase.h"

void UProject1GameViewportClientBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DetectMouseMove();
}

bool UProject1GameViewportClientBase::InputKey(const FInputKeyEventArgs& EventArgs)
{
	UpdateUsingGamepadState(EventArgs.Key.IsGamepadKey());
	return Super::InputKey(EventArgs);
}

bool UProject1GameViewportClientBase::DetectMouseMove()
{
	FVector2D CurrentMousePosition = {};

	// GetMousePosition returns false if there is no associated mouse device.
	if (!GetMousePosition(CurrentMousePosition))
	{
		return false;
	}

	if (CurrentMousePosition != PreviousMousePosition)
	{
		// Mouse position has changed.
		OnMouseMoved(CurrentMousePosition - PreviousMousePosition);
		PreviousMousePosition = CurrentMousePosition;
		return true;
	}

	// Mouse position has not changed.
	return false;
}

void UProject1GameViewportClientBase::OnMouseMoved(const FVector2D& MouseMoveDelta)
{
	UpdateUsingGamepadState(false);
}

void UProject1GameViewportClientBase::UpdateUsingGamepadState(bool GamepadInput)
{
	static bool FirstCall{ true };
	if (FirstCall)
	{
		FirstCall = false;
		ChangeGamepadState(true);
		return;
	}

	if (GamepadInput == bUsingGamepad)
	{
		return;
	}

	ChangeGamepadState(GamepadInput);
}

void UProject1GameViewportClientBase::ChangeGamepadState(bool UsingGamepad)
{
	bUsingGamepad = UsingGamepad;
	OnInputDeviceChangedDelegate.Broadcast(UsingGamepad);
}
