// Fill out your copyright notice in the Description page of Project Settings.


#include "SettingUserWidgetBase.h"
#include "Components/TextBlock.h"

USettingUserWidgetBase::USettingUserWidgetBase()
	: SettingLabelText(FText::FromString(TEXT("Default setting label"))),
	SettingDescriptionText(FText::FromString(TEXT("No description"))),
	OnGetDefaultSettingValueDelegate({}),
	OwningSettingsPage(nullptr)
{
}

bool USettingUserWidgetBase::HasSettingValueChanged() const
{
	// Base class implementation is empty
	return false;
}

void USettingUserWidgetBase::FocusSetting()
{
	bFocused = true;
	OnSettingFocused();
}

void USettingUserWidgetBase::UnfocusSetting()
{
	bFocused = false;
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
	OnGetDefaultSettingValueDelegate.Broadcast();
}

void USettingUserWidgetBase::NativePreConstruct()
{
	Super::NativePreConstruct();

	// Update setting label text
	if (UTextBlock* SettingLabelTextBlock = GetSettingLabelTextBlock())
	{
		SettingLabelTextBlock->SetText(FText::FromString(GetSettingLabel().ToString() + TEXT(":")));
	}
}
