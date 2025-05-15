// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG/Project1UserWidgetBase.h"
#include "SaveSlotWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSaveSlotSelectedSignature);

/**
 * 
 */
UCLASS()
class USaveSlotWidget : public UProject1UserWidgetBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnSaveSlotSelectedSignature OnSaveSlotSelectedDelegate{};
};
