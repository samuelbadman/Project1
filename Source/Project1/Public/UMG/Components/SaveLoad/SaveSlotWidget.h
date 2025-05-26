// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG/Project1UserWidgetBase.h"
#include "SaveSlotWidget.generated.h"

class UProject1ButtonBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSaveSlotSelectedSignature, USaveSlotWidget*, SaveSlot);

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

private:
	// Id used to reference the data for the save slot stored inside the game instance's save manager object
	int32 SaveSlotDataId{ -1 };

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "SaveSlotWidget")
	UProject1ButtonBase* GetBackingButton() const;

	void SetSaveSlotDataId(const int32 Id) { SaveSlotDataId = Id; }

	// Returns a copy of the FName. Cannot return a reference as the save slot name might be unretrievable if save SaveSlotDataId is invalid
	UFUNCTION(BlueprintCallable, Category = "SaveSlotWidget")
	FName GetUniqueSaveSlotName() const;
};
