// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserWidgets/Screens/ScreenUserWidgetBase.h"
#include "TitleScreenMainMenuScreen.generated.h"

class UUIInputAction;

/**
 * 
 */
UCLASS()
class UTitleScreenMainMenuScreen : public UScreenUserWidgetBase
{
	GENERATED_BODY()

private:
	void SetupUIInputActionEvents() override;
};
