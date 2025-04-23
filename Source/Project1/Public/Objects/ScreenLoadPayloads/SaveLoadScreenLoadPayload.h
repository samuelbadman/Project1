// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/ScreenLoadPayloads/ScreenWidgetLoadPayloadBase.h"
#include "SaveLoadScreenLoadPayload.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT1_API USaveLoadScreenLoadPayload : public UScreenWidgetLoadPayloadBase
{
	GENERATED_BODY()
	
public:
	// Is the screen being loaded to perform a save or load operation. Marking this as false means that the screen will be loaded for load operations whereas, marking this
	// this as true will mean that the screen will be loaded for save operations
	UPROPERTY(BlueprintReadWrite, Category = "SaveLoadScreenLoadPayload")
	bool bSaving{ true };
};
