// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG/Screens/ScreenUserWidgetBase.h"
#include "GameHUDScreen.generated.h"

class UCompassBarUserWidget;

/**
 * 
 */
UCLASS()
class UGameHUDScreen : public UScreenUserWidgetBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	UCompassBarUserWidget* GetCompassBarWidget() const;
};
