// Fill out your copyright notice in the Description page of Project Settings.


#include "SettingUserWidgetBase.h"

void USettingUserWidgetBase::FocusSetting()
{
	OnSettingFocused();
}

void USettingUserWidgetBase::UnfocusSetting()
{
	OnSettingUnfocused();
}

ESettingInputResult USettingUserWidgetBase::ProcessConfirmInput()
{
	// Base class implementation is empty and does not handle the input
	return ESettingInputResult::Unhandled;
}

ESettingInputResult USettingUserWidgetBase::ProcessNavigationInput(const FVector2D& NavigationInput)
{
	// Base class implementation is empty and does not handle the input
	return ESettingInputResult::Unhandled;
}
