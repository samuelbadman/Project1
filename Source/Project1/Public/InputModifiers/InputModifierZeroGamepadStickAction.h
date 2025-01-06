// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputModifiers.h"
#include "InputModifierZeroGamepadStickAction.generated.h"

/**
 * 
 */
UCLASS(NotBlueprintable, meta = (DisplayName = "Zero Gamepad Stick Action Input"))
class PROJECT1_API UInputModifierZeroGamepadStickAction : public UInputModifier
{
	GENERATED_BODY()
	
private:
	FInputActionValue ModifyRaw_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue CurrentValue, float DeltaTime) override;
};
