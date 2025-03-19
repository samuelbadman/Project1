// Fill out your copyright notice in the Description page of Project Settings.


#include "SettingsPageWidget.h"
#include "UMG/Components/Settings/SettingWidgets/SettingUserWidgetBase.h"
#include "Components/PanelWidget.h"
#include "FunctionLibraries/Project1MathLibrary.h"

USettingsPageWidget::USettingsPageWidget()
	: PageSettingWidgets({}),
	FocusedPageSettingIndex(INDEX_NONE)
{
}

void USettingsPageWidget::Show()
{
	// Show the page widget
	SetVisibility(ESlateVisibility::HitTestInvisible);

	// Focus first setting widget
	FocusSetting(0);

	for (USettingUserWidgetBase* Setting : PageSettingWidgets)
	{
		Setting->OnSettingShown();
	}
}

void USettingsPageWidget::Collapse()
{
	// Collapse the page widget
	SetVisibility(ESlateVisibility::Collapsed);

	ClearSettingFocus();

	for (USettingUserWidgetBase* Setting : PageSettingWidgets)
	{
		Setting->OnSettingCollapsed();
	}
}

void USettingsPageWidget::FocusSettingWidget(USettingUserWidgetBase* Setting)
{
	FocusSetting(PageSettingWidgets.Find(Setting));
}

void USettingsPageWidget::OnConfirmInput()
{
	// Pass the confirm input to the focused setting
	if (USettingUserWidgetBase* FocusedSetting = GetFocusedSetting())
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
	if (USettingUserWidgetBase* FocusedSetting = GetFocusedSetting())
	{
		// If the setting did not handle the input, handle it in the page widget
		if (FocusedSetting->ProcessNavigationInput(NavigationInput) == ESettingInputResult::Unhandled)
		{
			// Assumes settings are layed out in a vertical list
			if (NavigationInput.Y == 0.0f)
			{
				return;
			}

			FocusSetting(UProject1MathLibrary::WrapIncrementArrayIndex(FocusedPageSettingIndex, PageSettingWidgets.Num(), -StaticCast<int32>(NavigationInput.Y)));
		}
	}
}

void USettingsPageWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	BuildPageSettingWidgetsArray();
}

void USettingsPageWidget::BuildPageSettingWidgetsArray()
{
	if (UPanelWidget* SettingWidgetsContainer = GetSettingWidgetsContainer())
	{
		const TArray<UWidget*> SettingWidgetsContainerChildren{ SettingWidgetsContainer->GetAllChildren() };

		PageSettingWidgets.Reserve(SettingWidgetsContainerChildren.Num());

		for (UWidget* Child : SettingWidgetsContainerChildren)
		{
			if (USettingUserWidgetBase* Setting = Cast<USettingUserWidgetBase>(Child))
			{
				Setting->InitializeSetting(this);
				PageSettingWidgets.Add(Setting);
			}
		}

		PageSettingWidgets.Shrink();
	}
#if WITH_EDITOR
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("[%s] FAILED TO BUILD PAGE SETTING WIDGETS ARRAY."), *GetName()));
	}
#endif
}

void USettingsPageWidget::FocusSetting(int32 SettingIndex)
{
	// Cannot focus setting with invalid index
	if (!PageSettingWidgets.IsValidIndex(SettingIndex))
	{
		return;
	}

	// If there is currently a focused setting, unfocus it first
	if (PageSettingWidgets.IsValidIndex(FocusedPageSettingIndex))
	{
		PageSettingWidgets[FocusedPageSettingIndex]->UnfocusSetting();
	}

	// Focus the new setting
	PageSettingWidgets[SettingIndex]->FocusSetting();
	FocusedPageSettingIndex = SettingIndex;

	// Notify blueprint a new setting has been focused so that it can handle the event
	OnSettingFocused(PageSettingWidgets[SettingIndex]);
}

TObjectPtr<USettingUserWidgetBase> USettingsPageWidget::GetFocusedSetting() const
{
	return (PageSettingWidgets.IsValidIndex(FocusedPageSettingIndex)) ? PageSettingWidgets[FocusedPageSettingIndex] : nullptr;
}

void USettingsPageWidget::ClearSettingFocus()
{
	if (USettingUserWidgetBase* FocusedSetting = GetFocusedSetting())
	{
		FocusedSetting->UnfocusSetting();
	}

	FocusedPageSettingIndex = INDEX_NONE;
}
