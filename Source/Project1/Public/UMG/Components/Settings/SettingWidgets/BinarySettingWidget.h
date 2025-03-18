// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SettingUserWidgetBase.h"
#include "BinarySettingWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT1_API UBinarySettingWidget : public USettingUserWidgetBase
{
	GENERATED_BODY()
	
private:
	ESettingInputResult ProcessConfirmInput() override;
};
