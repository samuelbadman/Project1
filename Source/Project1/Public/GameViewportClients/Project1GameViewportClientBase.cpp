// Fill out your copyright notice in the Description page of Project Settings.


#include "Project1GameViewportClientBase.h"

void UProject1GameViewportClientBase::Init(FWorldContext& WorldContext, UGameInstance* OwningGameInstance, bool bCreateNewAudioDevice)
{
	Super::Init(WorldContext, OwningGameInstance, bCreateNewAudioDevice);

	// Set detect mouse move timer
	GetWorld()->GetTimerManager().SetTimer(DetectMouseMoveTimerHandle, this, &UProject1GameViewportClientBase::DetectMouseMove, DetectMouseMoveInterval, true);
}

bool UProject1GameViewportClientBase::InputKey(const FInputKeyEventArgs& EventArgs)
{
	UpdateUsingGamepadState(EventArgs.Key.IsGamepadKey());
	return Super::InputKey(EventArgs);
}

void UProject1GameViewportClientBase::DetectMouseMove()
{
	FVector2D CurrentMousePosition = {};

	// GetMousePosition returns false if there is no associated mouse device.
	if (!GetMousePosition(CurrentMousePosition))
	{
		return;
	}

	if (CurrentMousePosition != PreviousMousePosition)
	{
		// Mouse position has changed.
		OnMouseMoved(CurrentMousePosition, PreviousMousePosition, (CurrentMousePosition - PreviousMousePosition));
		PreviousMousePosition = CurrentMousePosition;
		return;
	}

	// Mouse position has not changed.
	return;
}

void UProject1GameViewportClientBase::OnMouseMoved(const FVector2D& NewMousePosition, const FVector2D& OldMousePosition, const FVector2D& MouseMoveDelta)
{
	UpdateUsingGamepadState(false);
	OnMouseMovedDelegate.Broadcast(NewMousePosition, OldMousePosition, MouseMoveDelta);
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
