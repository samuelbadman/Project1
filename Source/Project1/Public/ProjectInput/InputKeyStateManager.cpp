// Fill out your copyright notice in the Description page of Project Settings.


#include "InputKeyStateManager.h"

void UInputKeyStateManager::SetKeyState(const FKey& Key, const EInputKeyState InputKeyState)
{
	KeyStates.Add(Key, InputKeyState);
}

void UInputKeyStateManager::SetKeyStateFromInputEvent(const FKey& Key, const EInputEvent InputEvent)
{
	KeyStates.Add(Key, GetInputKeyStateFromInputEvent(InputEvent));
}

bool UInputKeyStateManager::IsKeyPressed(const FKey& Key) const
{
	return (GetKeyState(Key) == EInputKeyState::IKS_Pressed);
}

EInputKeyState UInputKeyStateManager::GetInputKeyStateFromInputEvent(const EInputEvent InputEvent) const
{
	return ((InputEvent == EInputEvent::IE_Pressed) || (InputEvent == EInputEvent::IE_Repeat)) ? EInputKeyState::IKS_Pressed : EInputKeyState::IKS_Released;
}

EInputKeyState UInputKeyStateManager::GetKeyState(const FKey& Key) const
{
	return KeyStates.FindRef(Key);
}
