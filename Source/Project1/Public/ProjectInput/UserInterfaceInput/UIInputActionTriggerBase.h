// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UIInputActionTriggerBase.generated.h"

struct FUIInputActionValue;

/**
 * 
 */
UCLASS(BlueprintType, EditInlineNew, DefaultToInstanced)
class UUIInputActionTriggerBase : public UObject
{
	GENERATED_BODY()
	
public:
	// Determines whether the input value should trigger the input action based on the rules implemented by the trigger class
	virtual bool Evaluate(const float RawInputValue, const EInputEvent InputEvent) const { return false; }
};
