// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserWidgets/Project1UserWidgetBase.h"
#include "GameplayTagContainer.h"
#include "HUDs/Project1HUDBase.h"
#include "ScreenUserWidgetBase.generated.h"

/**
 *
 */
UCLASS()
class PROJECT1_API UScreenUserWidgetBase : public UProject1UserWidgetBase
{
	GENERATED_BODY()

private:
	// The name of the UI widget layer that owns this screen. The name of the widget layer the screen widget was pushed to
	FGameplayTag OwningLayerName{};

public:
	void SetOwningLayerName(const FGameplayTag& LayerName);

	UFUNCTION(BlueprintImplementableEvent)
	void OnPushedToLayerStack();

	UFUNCTION(BlueprintImplementableEvent)
	void OnShown();

	UFUNCTION(BlueprintImplementableEvent)
	void OnCollapsed();

	UFUNCTION(BlueprintImplementableEvent)
	void OnPoppedFromLayerStack();

	UFUNCTION(BlueprintImplementableEvent)
	void ConsumeLoadPayload(UScreenWidgetLoadPayloadBase* LoadPayload);

	// Called when the widget is pushed to a widget layer stack
	virtual void NativeOnPushedToLayerStack() {};
	// Called when the widget is manually shown on top of a widget layer stack by calling ShowTop on the layer
	virtual void NativeOnShown() {};
	// Called when the widget is manually collapsed on top of a widget layer stack by calling CollapseTop on the layer
	virtual void NativeOnCollapsed() {};
	// Called when widget is popped from a widget layer stack
	virtual void NativeOnPoppedFromLayerStack() {};
	// Called when the widget has finished loading if a valid load payload object was provided when pushing the screen widget to a widget layer
	virtual void NativeConsumeLoadPayload(TObjectPtr<UScreenWidgetLoadPayloadBase> LoadPayload) {};

	FORCEINLINE const FGameplayTag& GetOwningLayerName() const { return OwningLayerName; }
};
