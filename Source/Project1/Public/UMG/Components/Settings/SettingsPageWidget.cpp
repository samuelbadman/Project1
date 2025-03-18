// Fill out your copyright notice in the Description page of Project Settings.


#include "SettingsPageWidget.h"
#include "UMG/Components/Settings/SettingWidgets/SettingUserWidgetBase.h"
#include "Components/ScrollBox.h"

USettingsPageWidget::USettingsPageWidget()
	: FocusedSetting(nullptr)
{
}

void USettingsPageWidget::Show()
{
	// Show the page widget
	SetVisibility(ESlateVisibility::HitTestInvisible);

	// Get the page's default setting to focus and focus it if it is valid
	if (USettingUserWidgetBase* DefaultFocusedSetting = GetDefaultFocusedSetting())
	{
		FocusSetting(DefaultFocusedSetting);
	}
}

void USettingsPageWidget::Collapse()
{
	// Collapse the page widget
	SetVisibility(ESlateVisibility::Collapsed);
}

void USettingsPageWidget::OnConfirmInput()
{
	// Pass the confirm input to the focused setting
	if (IsValid(FocusedSetting))
	{
		// If the setting did not handle the input, handle it in the page widget
		if (FocusedSetting->ProcessConfirmInput() == ESettingInputResult::Unhandled)
		{
			// Handle unhandled confirm input in the screen widget here
		}
	}
}

void USettingsPageWidget::OnNavigationInput(const FVector2D& NavigationInput)
{
	// Pass the navigation input to the focused setting
	if (IsValid(FocusedSetting))
	{
		// If the setting did not handle the input, handle it in the page widget by navigating through the setting widgets
		if (FocusedSetting->ProcessNavigationInput(NavigationInput) == ESettingInputResult::Unhandled)
		{
			if (NavigationInput.Y == 0.0f)
			{
				return;
			}

			const EWidgetNavigationDirection NavDirection{ (NavigationInput.Y > 0.0f) ? EWidgetNavigationDirection::Up : EWidgetNavigationDirection::Down };
			// Assume a setting widget is set as the setting's navigation widget
			const TObjectPtr<USettingUserWidgetBase> NavSetting{ CastChecked<USettingUserWidgetBase>(FocusedSetting->GetNavigationWidget(NavDirection).Get()) };
			FocusSetting(NavSetting);
		}
	}
}

void USettingsPageWidget::FocusSetting(TObjectPtr<USettingUserWidgetBase> SettingToFocus)
{
	// If there is currently a focused setting, unfocus it first
	if (IsValid(FocusedSetting))
	{
		FocusedSetting->UnfocusSetting();
	}

	// Focus the new setting
	SettingToFocus->FocusSetting();
	FocusedSetting = SettingToFocus;

	// Scroll the focused setting into view if there is a valid scroll box
	if (UScrollBox* ScrollBox = GetScrollBox())
	{
		ScrollBox->ScrollWidgetIntoView(SettingToFocus);
	}
}
