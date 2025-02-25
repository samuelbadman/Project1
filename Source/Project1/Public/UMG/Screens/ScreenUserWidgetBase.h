// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG/Project1UserWidgetBase.h"
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

public:
	UPROPERTY(EditAnywhere)
	bool bBlockLowerPriorityLayerInput{ true };

private:
	// A reference to the HUD
	TObjectPtr<AProject1HUDBase> Project1HUD{ nullptr };
	// A reference to the widget layer the screen is in
	TObjectPtr<ULayerUserWidgetBase> OwningLayer{ nullptr };

public:
	void SetOwningLayer(TObjectPtr<ULayerUserWidgetBase> Layer);

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
	virtual void NativeOnPushedToLayerStack();
	// Called when the widget is manually shown on top of a widget layer stack by calling ShowTop on the layer
	virtual void NativeOnShown();
	// Called when the widget is manually collapsed on top of a widget layer stack by calling CollapseTop on the layer
	virtual void NativeOnCollapsed();
	// Called when widget is popped from a widget layer stack
	virtual void NativeOnPoppedFromLayerStack();
	// Called when the widget has finished loading if a valid load payload object was provided when pushing the screen widget to a widget layer
	virtual void NativeConsumeLoadPayload(TObjectPtr<UScreenWidgetLoadPayloadBase> LoadPayload);

	const FGameplayTag& GetOwningLayerName() const;
	bool CanReceiveInput() const;

	FORCEINLINE TObjectPtr<ULayerUserWidgetBase> GetOwningLayer() const { return OwningLayer; }

private:
	void NativeOnInitialized() override;

	bool IsTopOfOwningLayer() const;
	bool IsInputBlockedByHigherLayer() const;
};
