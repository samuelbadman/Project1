// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIInputActionTriggerBase.h"
#include "UIInputActionTrigger_Repeat.generated.h"

/**
 * 
 */
UCLASS(meta = (DisplayName = "Repeat"))
class UUIInputActionTrigger_Repeat: public UUIInputActionTriggerBase
{
	GENERATED_BODY()
	
private:
	bool Evaluate(const float RawInputValue, const EInputEvent InputEvent) const override;
};
