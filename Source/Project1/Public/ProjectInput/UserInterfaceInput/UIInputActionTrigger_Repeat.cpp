// Fill out your copyright notice in the Description page of Project Settings.


#include "UIInputActionTrigger_Repeat.h"
#include "UIInputActionValue.h"

bool UUIInputActionTrigger_Repeat::Evaluate(const float RawInputValue, const EInputEvent InputEvent) const
{
	return ((RawInputValue == FUIInputActionValue::PressedValue) &&
		(InputEvent == EInputEvent::IE_Repeat));
}
