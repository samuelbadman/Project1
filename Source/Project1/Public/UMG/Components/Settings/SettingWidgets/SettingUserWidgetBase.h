// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG/Project1UserWidgetBase.h"
#include "SettingUserWidgetBase.generated.h"

enum class ESettingInputResult : uint8
{
	Handled,
	Unhandled
};

/**
 * 
 */
UCLASS()
class PROJECT1_API USettingUserWidgetBase : public UProject1UserWidgetBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent, Category = "SettingUserWidgetBase")
	void OnSettingFocused();

	UFUNCTION(BlueprintImplementableEvent, Category = "SettingUserWidgetBase")
	void OnSettingUnfocused();

	virtual void FocusSetting();
	virtual void UnfocusSetting();
	virtual ESettingInputResult ProcessConfirmInput();
	virtual ESettingInputResult ProcessNavigationInput(const FVector2D& NavigationInput);
};
