// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG/Project1UserWidgetBase.h"
#include "DynamicModalOptionUserWidget.generated.h"

class UProject1ButtonBase;

/**
 * 
 */
UCLASS()
class PROJECT1_API UDynamicModalOptionUserWidget : public UProject1UserWidgetBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent)
	void SetOptionText(const FText& Text);

	UFUNCTION(BlueprintImplementableEvent)
	UProject1ButtonBase* GetButton();
};
