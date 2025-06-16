// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG/Project1UserWidgetBase.h"
#include "SettingUserWidgetBase.generated.h"

class USettingsPageWidget;
class UTextBlock;

enum class ESettingInputResult : uint8
{
	Handled,
	Unhandled
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGetDefaultSettingValueDelegate);

/**
 *
 */
UCLASS()
class PROJECT1_API USettingUserWidgetBase : public UProject1UserWidgetBase
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	FText SettingLabelText;

	UPROPERTY(EditAnywhere, meta = (MultiLine = "true"))
	FText SettingDescriptionText;

	UPROPERTY(BlueprintAssignable, meta = (DisplayName = "On Get Default Setting Value"))
	FOnGetDefaultSettingValueDelegate OnGetDefaultSettingValueDelegate;

	// The settings page widget that owns this setting
	TObjectPtr<USettingsPageWidget> OwningSettingsPage;

public:
	USettingUserWidgetBase();

	UFUNCTION(BlueprintImplementableEvent, Category = "BinarySettingWidget")
	UTextBlock* GetSettingLabelTextBlock();

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

	UFUNCTION(BlueprintCallable, Category = "SettingUserWidgetBase")
	const FText& GetSettingLabel() const { return SettingLabelText; }

	UFUNCTION(BlueprintCallable, Category = "SettingUserWidgetBase")
	const FText& GetSettingDescription() const { return SettingDescriptionText; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "SettingUserWidgetBase")
	virtual bool HasSettingValueChanged() const;

	virtual void FocusSetting();
	virtual void UnfocusSetting();
	virtual ESettingInputResult ProcessConfirmInput();
	virtual ESettingInputResult ProcessNavigationInput(const FVector2D& NavigationInput);

	void InitializeSetting(TObjectPtr<USettingsPageWidget> OwningPage);

protected:
	virtual void NativePreConstruct() override;
};
