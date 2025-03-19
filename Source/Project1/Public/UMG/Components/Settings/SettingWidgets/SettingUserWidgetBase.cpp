// Fill out your copyright notice in the Description page of Project Settings.


#include "SettingUserWidgetBase.h"
#include "Components/TextBlock.h"

USettingUserWidgetBase::USettingUserWidgetBase()
	: SettingLabel(TEXT("Default Label")),
	OnGetSettingValueDelegate({}),
	OwningSettingsPage(nullptr)
{
}

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

void USettingUserWidgetBase::InitializeSetting(TObjectPtr<USettingsPageWidget> OwningPage)
{
	// Set owning setting page
	OwningSettingsPage = OwningPage;

	// Notify blueprint to get current value of setting and update widget with value
	OnGetSettingValueDelegate.Broadcast();
}

void USettingUserWidgetBase::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (UTextBlock* SettingLabelTextBlock = GetSettingLabelTextBlock())
	{
		SettingLabelTextBlock->SetText(FText::FromString(SettingLabel + TEXT(":")));
	}
}
