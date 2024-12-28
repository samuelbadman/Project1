// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InputKeyStateManager.generated.h"

enum class EInputKeyState : uint8
{
	IKS_Released = 0,
	IKS_Pressed
};

/**
 * 
 */
UCLASS()
class PROJECT1_API UInputKeyStateManager : public UObject
{
	GENERATED_BODY()
	
private:
	TMap<FKey, EInputKeyState> KeyStates{};

public:
	void SetKeyState(const FKey& Key, const EInputKeyState InputKeyState);
	void SetKeyStateFromInputEvent(const FKey& Key, const EInputEvent InputEvent);
	bool IsKeyPressed(const FKey& Key) const;
	EInputKeyState GetInputKeyStateFromInputEvent(const EInputEvent InputEvent) const;
	EInputKeyState GetKeyState(const FKey& Key) const;
};
