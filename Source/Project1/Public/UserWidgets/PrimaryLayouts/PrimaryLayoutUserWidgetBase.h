// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserWidgets/Project1UserWidgetBase.h"
#include "GameplayTagContainer.h"
#include "PrimaryLayoutUserWidgetBase.generated.h"

class ULayerUserWidgetBase;
class UScreenUserWidgetBase;

/**
 * 
 */
UCLASS()
class PROJECT1_API UPrimaryLayoutUserWidgetBase : public UProject1UserWidgetBase
{
	GENERATED_BODY()
	
private:
	TMap<FGameplayTag, TObjectPtr<ULayerUserWidgetBase>> Layers{};

public:
	UFUNCTION(BlueprintCallable)
	bool RegisterLayer(const FGameplayTag& LayerName, ULayerUserWidgetBase* LayerWidget);

	UFUNCTION(BlueprintCallable)
	bool UnregisterLayer(const FGameplayTag& LayerName);

	UFUNCTION(BlueprintCallable)
	void PushContentToLayer(const FGameplayTag& LayerName, const TSoftClassPtr<UScreenUserWidgetBase>& WidgetClass);

	UFUNCTION(BlueprintCallable)
	void PopContentFromLayer(const FGameplayTag& LayerName);

	UFUNCTION(BlueprintCallable)
	ULayerUserWidgetBase* GetRegisteredLayer(const FGameplayTag& LayerName);
};
