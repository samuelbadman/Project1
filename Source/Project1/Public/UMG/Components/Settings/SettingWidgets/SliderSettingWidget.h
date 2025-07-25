// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG/Components/Settings/SettingWidgets/SettingUserWidgetBase.h"
#include "SliderSettingWidget.generated.h"

class USpacer;
class USizeBox;
class UProject1ButtonBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSliderValueChangedDelegate, float, NewValue);

/**
 * 
 */
UCLASS()
class USliderSettingWidget : public USettingUserWidgetBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable, Category = "SliderSettingWidget")
	FOnSliderValueChangedDelegate OnSliderValueChangedDelegate{};

private:
	// TODO: Move label text and spacer into its own widget that can be added to setting widgets and put this dynamically adjustable spacer padding functionality into the new 
	// widget to prevent reproducing this code in each setting widget
	UPROPERTY(EditAnywhere)
	FMargin LabelMargin{ 0.0 };

	UPROPERTY(EditAnywhere)
	float SliderBarSize{ 100.0f };

	UPROPERTY(EditAnywhere)
	float SliderMinValue{ 0.0f };

	UPROPERTY(EditAnywhere)
	float SliderMaxValue{ 100.0f };

	// The speed the slider head button widget is interpolated at when making adjustments to it. This is a visual only effect and does not affect the actual value of the slider setting
	UPROPERTY(EditAnywhere)
	float SliderHeadButtonInterpSpeed{ 7.5f };

	UPROPERTY(EditAnywhere)
	float GamepadSliderAdjustmentRate{ 60.0f };

	TObjectPtr<UWorld> World{ nullptr };
	TObjectPtr<UGameViewportClient> GameViewportClient{ nullptr };
	TObjectPtr<UWidget> SliderHeadButtonParentWidget{ nullptr };
	TObjectPtr<UProject1ButtonBase> SliderHeadButtonWidget{ nullptr };
	TObjectPtr<UPanelWidget> SliderBarPortionParentWidget{ nullptr };
	FDelegateHandle MouseMovedDelegateHandle{};

	float SliderValue{ 0.0f };
	float DefaultSliderValue{ 0.0f };
	float TargetSliderHeadButtonRenderTranslationOffsetX{ 0.0f };

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "SliderSettingWidget")
	USpacer* GetLabelSpacer();

	UFUNCTION(BlueprintImplementableEvent, Category = "SliderSettingWidget")
	UProject1ButtonBase* GetSliderHeadButton();

	UFUNCTION(BlueprintImplementableEvent, Category = "SliderSettingWidget")
	UPanelWidget* GetSliderBarPortionParent() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "SliderSettingWidget")
	FVector2D GetSliderHeadButtonDimensions() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "SliderSettingWidget")
	UWidget* GetSliderHeadButtonParent();

	UFUNCTION(BlueprintImplementableEvent, Category = "SliderSettingWidget")
	USizeBox* GetSliderBarSizeBox();

	// Changes the value of the slider
	UFUNCTION(BlueprintCallable, Category = "SliderSettingWidget")
	void SetSliderValue(float NewValue);

	// Returns the current value the slider bar is set to
	UFUNCTION(BlueprintCallable, Category = "SliderSettingWidget")
	float GetSliderValue() const;

	// Sets the default value of the slider widget. The default value should be set when the slider widget is initialized and is used to know whether the value of the slider has been
	// changed
	UFUNCTION(BlueprintCallable, Category = "SliderSettingWidget")
	void SetDefaultSliderValue(float NewDefaultValue);

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeOnInitialized() override;
	bool HasSettingValueChanged() const override;

private:
	virtual ESettingInputResult ProcessContinuousNavigationInput(const FVector2D& NavigationInput) override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION()
	void OnSliderHeadButtonClicked(UProject1ButtonBase* ButtonClicked);
	UFUNCTION()
	void OnSliderHeadButtonReleased(UProject1ButtonBase* ButtonReleased);

	void OnMouseMoved(const FVector2D& NewMousePosition, const FVector2D& OldMousePosition, const FVector2D& MouseMoveDelta);

	float GetSliderValueFromRenderTranslation(const double XTranslation) const;
	float GetRenderTranslationFromSliderValue(const float SliderValue) const;
	void UpdateSliderValue(const float NewValue);
};
