// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG/Project1UserWidgetBase.h"
#include "SettingsPageWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT1_API USettingsPageWidget : public UProject1UserWidgetBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "SettingsPageWidget")
	void Show();

	UFUNCTION(BlueprintCallable, Category = "SettingsPageWidget")
	void Collapse();
};
