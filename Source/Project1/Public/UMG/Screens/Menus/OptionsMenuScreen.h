// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG/Screens/Menus/MenuScreenBase.h"
#include "OptionsMenuScreen.generated.h"

class UProject1ButtonBase;

/**
 * 
 */
UCLASS()
class PROJECT1_API UOptionsMenuScreen : public UMenuScreenBase
{
	GENERATED_BODY()
	
private:


public:
	UOptionsMenuScreen();

	UFUNCTION(BlueprintCallable)
	void RegisterMenuButtons(const TArray<UProject1ButtonBase*>& Buttons, int32 DefaultHoveredButtonIndex = 0);
};
