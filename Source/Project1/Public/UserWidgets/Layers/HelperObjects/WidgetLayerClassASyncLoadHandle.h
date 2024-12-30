// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"
#include "WidgetLayerClassASyncLoadHandle.generated.h"

class ULayerUserWidgetBase;
struct FStreamableHandle;

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
	FGameplayTag WidgetIdentifier{};

	void OnLoadedClass();
};
