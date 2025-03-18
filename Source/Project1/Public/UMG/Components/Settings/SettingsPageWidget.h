// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG/Project1UserWidgetBase.h"
#include "SettingsPageWidget.generated.h"

class USettingUserWidgetBase;
class UScrollBox;

/**
 *
 */
UCLASS()
class PROJECT1_API USettingsPageWidget : public UProject1UserWidgetBase
{
	GENERATED_BODY()

private:
	TObjectPtr<USettingUserWidgetBase> FocusedSetting;

public:
	USettingsPageWidget();

	// All settings pages contain a scroll box that contains the list of setting widgets for the page
	UFUNCTION(BlueprintImplementableEvent, Category = "SettingsPageWidget")
	UScrollBox* GetScrollBox();

	// Returns the setting widget that should be focused by default when the page is opened
	UFUNCTION(BlueprintImplementableEvent, Category = "SettingsPageWidget")
	USettingUserWidgetBase* GetDefaultFocusedSetting();

	UFUNCTION(BlueprintCallable, Category = "SettingsPageWidget")
	void Show();

	UFUNCTION(BlueprintCallable, Category = "SettingsPageWidget")
	void Collapse();

	void OnConfirmInput();
	void OnNavigationInput(const FVector2D& NavigationInput);

private:
	void FocusSetting(TObjectPtr<USettingUserWidgetBase> SettingToFocus);
};
