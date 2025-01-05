// Fill out your copyright notice in the Description page of Project Settings.


#include "UIInputActionTrigger_Released.h"
#include "UIInputActionValue.h"

bool UUIInputActionTrigger_Released::Evaluate(const float RawInputValue) const
{
	return RawInputValue == FUIInputActionValue::ReleasedValue;
}
