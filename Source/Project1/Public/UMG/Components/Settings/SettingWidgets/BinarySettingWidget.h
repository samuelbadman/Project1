// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SettingUserWidgetBase.h"
#include "BinarySettingWidget.generated.h"

class USpacer;

UENUM()
enum class EBinarySettingValue : uint8
{
	Value1 UMETA(DisplayName = "Binary Setting Value 1"),
	Value2 UMETA(DisplayName = "Binary Setting Value 2")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBinarySettingValueChangedDelegate, EBinarySettingValue, NewValue);

/**
 * 
 */
UCLASS()
class PROJECT1_API UBinarySettingWidget : public USettingUserWidgetBase
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere)
	FMargin LabelMargin;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "Setting Value 1 Label"))
	FString SettingValue1Label;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "Setting Value 2 Label"))
	FString SettingValue2Label;

	UPROPERTY(BlueprintAssignable, meta = (DisplayName = "On Setting Value Changed"))
	FOnBinarySettingValueChangedDelegate OnSettingValueChangedDelegate;

	bool SettingValue;
	bool DefaultSettingValue;

public:
	UBinarySettingWidget();

	UFUNCTION(BlueprintImplementableEvent, Category = "BinarySettingWidget")
	UTextBlock* GetSettingValueLabelTextBlock();

	UFUNCTION(BlueprintImplementableEvent, Category = "BinarySettingWidget")
	USpacer* GetLabelSpacer();

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
	bool HasSettingValueChanged() const override;

	void UpdateSettingValue(bool NewValue);
	void UpdateSettingValueLabel();
};
