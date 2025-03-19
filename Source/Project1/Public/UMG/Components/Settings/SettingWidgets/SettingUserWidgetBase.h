// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG/Project1UserWidgetBase.h"
#include "SettingUserWidgetBase.generated.h"

class USettingsPageWidget;

enum class ESettingInputResult : uint8
{
	Handled,
	Unhandled
};

/**
 * 
 */
UCLASS()
class PROJECT1_API USettingUserWidgetBase : public UProject1UserWidgetBase
{
	GENERATED_BODY()
	
private:
	// The settings page widget that owns this setting
	TObjectPtr<USettingsPageWidget> OwningSettingsPage;

public:
	USettingUserWidgetBase();

	UFUNCTION(BlueprintImplementableEvent, Category = "SettingUserWidgetBase")
	void OnSettingFocused();

	UFUNCTION(BlueprintImplementableEvent, Category = "SettingUserWidgetBase")
	void OnSettingUnfocused();

	// Called when the setting page the setting user widget belongs to is shown
	UFUNCTION(BlueprintImplementableEvent, Category = "SettingUserWidgetBase")
	void OnSettingShown();

	// Called when the setting page the setting user widget belongs to is collapsed
	UFUNCTION(BlueprintImplementableEvent, Category = "SettingUserWidgetBase")
	void OnSettingCollapsed();

	UFUNCTION(BlueprintCallable, Category = "SettingUserWidgetBase")
	USettingsPageWidget* GetOwningSettingsPage() const { return OwningSettingsPage; }

	virtual void FocusSetting();
	virtual void UnfocusSetting();
	virtual ESettingInputResult ProcessConfirmInput();
	virtual ESettingInputResult ProcessNavigationInput(const FVector2D& NavigationInput);

	void SetOwningSettingsPage(TObjectPtr<USettingsPageWidget> Page);
};
