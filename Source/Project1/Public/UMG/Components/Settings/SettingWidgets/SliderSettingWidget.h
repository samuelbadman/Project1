// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG/Components/Settings/SettingWidgets/SettingUserWidgetBase.h"
#include "SliderSettingWidget.generated.h"

class USpacer;

/**
 * 
 */
UCLASS()
class USliderSettingWidget : public USettingUserWidgetBase
{
	GENERATED_BODY()
	
private:
	// TODO: Move label text and spacer into its own widget that can be added to setting widgets and put this dynamically adjustable spacer padding functionality into the new 
	// widget to prevent reproducing this code in each setting widget
	UPROPERTY(EditAnywhere)
	FMargin LabelMargin{ 50.0, 0.0, 0.0, 0.0 };

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "BinarySettingWidget")
	USpacer* GetLabelSpacer();

protected:
	virtual void NativePreConstruct() override;
};
