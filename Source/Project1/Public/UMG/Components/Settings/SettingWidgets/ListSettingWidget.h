// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SettingUserWidgetBase.h"
#include "ListSettingWidget.generated.h"

/**
 *
 */
UCLASS()
class PROJECT1_API UListSettingWidget : public USettingUserWidgetBase
{
	GENERATED_BODY()

private:
	ESettingInputResult ProcessNavigationInput(const FVector2D& NavigationInput) override;
};
