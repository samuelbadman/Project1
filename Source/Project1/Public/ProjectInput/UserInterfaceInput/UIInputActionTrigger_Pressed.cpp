// Fill out your copyright notice in the Description page of Project Settings.


#include "UIInputActionTrigger_Pressed.h"
#include "UIInputActionValue.h"

bool UUIInputActionTrigger_Pressed::Evaluate(const float RawInputValue) const
{
	return RawInputValue == FUIInputActionValue::PressedValue;
}
