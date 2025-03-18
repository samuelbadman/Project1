// Fill out your copyright notice in the Description page of Project Settings.


#include "SettingUserWidgetBase.h"

void USettingUserWidgetBase::FocusSetting()
{
	OnSettingFocused();
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, FString::Printf(TEXT("%s focused"), *GetName()));
}

void USettingUserWidgetBase::UnfocusSetting()
{
	OnSettingUnfocused();
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, FString::Printf(TEXT("%s unfocused"), *GetName()));
}

ESettingInputResult USettingUserWidgetBase::ProcessConfirmInput()
{
	// Base class implementation is empty
	return ESettingInputResult::Unhandled;
}

ESettingInputResult USettingUserWidgetBase::ProcessNavigationInput(const FVector2D& NavigationInput)
{
	// Base class implementation is empty
	return ESettingInputResult::Unhandled;
}
