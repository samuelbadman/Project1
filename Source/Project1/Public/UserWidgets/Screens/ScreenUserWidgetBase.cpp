// Fill out your copyright notice in the Description page of Project Settings.


#include "ScreenUserWidgetBase.h"

void UScreenUserWidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	SetupUIInputActionEvents();
}

void UScreenUserWidgetBase::SetUIInputActionValue(FUIInputActionValue& Value, const FUIInputActionKeyMapping& Mapping, float Data)
{
	if (Mapping.bMapInputTo2DAxis)
	{
		Value.Axis2D = Data * Mapping.ValueScale;
	}
	else
	{
		Value.Default1DAxis = Data * Mapping.ValueScale;
	}
}
