// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SettingUserWidgetBase.h"
#include "BinarySettingWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSettingValueChangedDelegate, bool, NewValue);

/**
 * 
 */
UCLASS()
class PROJECT1_API UBinarySettingWidget : public USettingUserWidgetBase
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, meta = (DisplayName = "Setting Value 1 Label"))
	FString SettingValue1Label;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "Setting Value 2 Label"))
	FString SettingValue2Label;

	UPROPERTY(BlueprintAssignable, meta = (DisplayName = "On Setting Value Changed"))
	FOnSettingValueChangedDelegate OnSettingValueChangedDelegate;

	bool SettingValue;

public:
	UBinarySettingWidget();

	UFUNCTION(BlueprintImplementableEvent, Category = "BinarySettingWidget")
	UTextBlock* GetSettingValueLabelTextBlock();

	// Flips the current setting value. Value 1 becomes value 2 and value 2 becomes value 1
	UFUNCTION(BlueprintCallable, Category = "BinarySettingWidget")
	void FlipSettingValue();

	// True sets the setting to value 1 while false sets the setting to value 2 without generating a value changed event
	UFUNCTION(BlueprintCallable, Category = "BinarySettingWidget")
	void SetDefaultSettingValue(bool NewValue);

	// True sets the setting to value 1 while false sets the setting to value 2 and generates a value changed event
	void SetSettingValue(bool NewValue);

private:
	void NativePreConstruct() override;
	ESettingInputResult ProcessConfirmInput() override;

	void UpdateSettingValue(bool NewValue);
	void UpdateSettingValueLabel();
};
