// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG/Project1UserWidgetBase.h"
#include "SettingsPageWidget.generated.h"

class USettingUserWidgetBase;
class UPanelWidget;

/**
 *
 */
UCLASS()
class PROJECT1_API USettingsPageWidget : public UProject1UserWidgetBase
{
	GENERATED_BODY()

private:
	TArray<TObjectPtr<USettingUserWidgetBase>> PageSettingWidgets;
	int32 FocusedPageSettingIndex;

public:
	USettingsPageWidget();

	UFUNCTION(BlueprintImplementableEvent, Category = "SettingsPageWidget")
	UPanelWidget* GetSettingWidgetsContainer();

	UFUNCTION(BlueprintImplementableEvent, Category = "SettingsPageWidget")
	void OnSettingFocused(USettingUserWidgetBase* FocusedSetting);

	UFUNCTION(BlueprintCallable, Category = "SettingsPageWidget")
	void Show();

	UFUNCTION(BlueprintCallable, Category = "SettingsPageWidget")
	void Collapse();

	UFUNCTION(BlueprintCallable, Category = "SettingsPageWidget")
	void FocusSettingWidget(USettingUserWidgetBase* Setting);

	void OnConfirmInput();
	void OnNavigationInput(const FVector2D& NavigationInput);

private:
	void NativeOnInitialized() override;

	void BuildPageSettingWidgetsArray();
	void FocusSetting(int32 SettingIndex);
	TObjectPtr<USettingUserWidgetBase> GetFocusedSetting() const;
	void ClearSettingFocus();
};
