// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WidgetInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT1_API UWidgetInputComponent : public UObject
{
	GENERATED_BODY()
	
public:
	void Initialize();

private:
	void OnPlayerInput(const FKey& Key, EInputEvent InputEvent);
};
