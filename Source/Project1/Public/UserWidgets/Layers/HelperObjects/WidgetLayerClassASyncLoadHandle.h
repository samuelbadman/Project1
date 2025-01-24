// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WidgetLayerClassASyncLoadHandle.generated.h"

class ULayerUserWidgetBase;
struct FStreamableHandle;
class UScreenWidgetLoadPayloadBase;

/**
 * 
 */
UCLASS(BlueprintType)
class PROJECT1_API UWidgetLayerClassASyncLoadHandle : public UObject
{
	GENERATED_BODY()
	
public:
	TObjectPtr<ULayerUserWidgetBase> WidgetLayer{ nullptr };
	TSharedPtr<FStreamableHandle> StreamableHandle{ nullptr };

	UPROPERTY() // Marked UPROPERTY so that the payload object is not deleted by garbage collection until the ASync load handle is destroyed
	TObjectPtr<UScreenWidgetLoadPayloadBase> LoadPayload{ nullptr };

	void OnLoadedClass();
};
