// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIInputActionTriggerBase.h"
#include "UIInputActionTrigger_Released.generated.h"

/**
 * 
 */
UCLASS(meta = (DisplayName = "Released"))
class UUIInputActionTrigger_Released: public UUIInputActionTriggerBase
{
	GENERATED_BODY()
	
private:
	bool Evaluate(const float RawInputValue) const override;
};
