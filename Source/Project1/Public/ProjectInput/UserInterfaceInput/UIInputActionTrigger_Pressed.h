// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIInputActionTriggerBase.h"
#include "UIInputActionTrigger_Pressed.generated.h"

/**
 * 
 */
UCLASS(meta = (DisplayName = "Pressed"))
class UUIInputActionTrigger_Pressed: public UUIInputActionTriggerBase
{
	GENERATED_BODY()
	
private:
	bool Evaluate(const float RawInputValue) const override;
};
