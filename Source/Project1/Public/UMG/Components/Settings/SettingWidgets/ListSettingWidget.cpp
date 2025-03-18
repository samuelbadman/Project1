// Fill out your copyright notice in the Description page of Project Settings.


#include "ListSettingWidget.h"

ESettingInputResult UListSettingWidget::ProcessNavigationInput(const FVector2D& NavigationInput)
{
	if (NavigationInput.X != 0.0f)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, FString::Printf(TEXT("%s handled navigation input"), *GetName()));
		return ESettingInputResult::Handled;
	}

	return ESettingInputResult::Unhandled;
}
