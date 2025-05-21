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
	FName UniqueSaveSlotName{NAME_None};

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "SaveSlotWidget")
	UProject1ButtonBase* GetBackingButton() const;

	void SetUniqueSaveSlotName(const FName& Name);
	UFUNCTION(BlueprintCallable, Category = "SaveSlotWidget")
	const FName& GetUniqueSaveSlotName() const { return UniqueSaveSlotName; }
};
