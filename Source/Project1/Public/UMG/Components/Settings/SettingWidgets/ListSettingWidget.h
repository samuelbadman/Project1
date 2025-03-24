// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SettingUserWidgetBase.h"
#include "ListSettingWidget.generated.h"

class UTextBlock;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnListSettingValueChangedDelegate, int32, NewValueIndex);

/**
 *
 */
UCLASS()
class PROJECT1_API UListSettingWidget : public USettingUserWidgetBase
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	TArray<FText> SettingValueLabels;

	UPROPERTY(BlueprintAssignable, meta = (DisplayName = "On Setting Value Changed"))
	FOnListSettingValueChangedDelegate OnSettingValueChangedDelegate;

	int32 CurrentSettingValueIndex;
	int32 DefaultSettingValueIndex;

public:
	UListSettingWidget();

	UFUNCTION(BlueprintImplementableEvent, Category = "ListSettingWidget")
	UTextBlock* GetSettingValueLabelTextBlock();

	UFUNCTION(BlueprintCallable, Category = "ListSettingWidget")
	void SetDefaultSettingValueIndex(int32 Index);

	UFUNCTION(BlueprintCallable, Category = "ListSettingWidget")
	void SetSettingValueIndex(int32 Index);

	// A positive increment will scroll through the setting value list right while a negative increment will scroll left
	UFUNCTION(BlueprintCallable, Category = "ListSettingWidget")
	void ScrollSettingValue(int32 Increment);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ListSettingWidget")
	const FText& GetSettingValueLabel(int32 SettingValueIndex) const;

private:
	ESettingInputResult ProcessNavigationInput(const FVector2D& NavigationInput) override;
	bool HasSettingValueChanged() const override;

	void UpdateSettingValue(int32 NewValueIndex);
};
