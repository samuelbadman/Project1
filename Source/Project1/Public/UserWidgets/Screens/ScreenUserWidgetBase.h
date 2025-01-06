// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserWidgets/Project1UserWidgetBase.h"
#include "GameplayTagContainer.h"
#include "HUDs/Project1HUDBase.h"
#include "ScreenUserWidgetBase.generated.h"

class UUIInputAction;
struct FUIInputActionValue;

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

	// Called when the widget is pushed to a widget layer stack
	virtual void NativeOnPushedToLayerStack() {};
	// Called when the widget is manually shown on top of a widget layer stack by calling ShowTop on the layer
	virtual void NativeOnShown() {};
	// Called when the widget is manually collapsed on top of a widget layer stack by calling CollapseTop on the layer
	virtual void NativeOnCollapsed() {};
	// Called when widget is popped from a widget layer stack
	virtual void NativeOnPoppedFromLayerStack() {};

	UFUNCTION(BlueprintImplementableEvent)
	void OnLeftClickTriggered(const FInputActionValue& Value);

	UFUNCTION(BlueprintImplementableEvent)
	void OnMiddleClickTriggered(const FInputActionValue& Value);

	UFUNCTION(BlueprintImplementableEvent)
	void OnRightClickTriggered(const FInputActionValue& Value);

	UFUNCTION(BlueprintImplementableEvent)
	void OnMouseWheelTriggered(const FInputActionValue& Value);

	UFUNCTION(BlueprintImplementableEvent)
	void OnNavigateTriggered(const FInputActionValue& Value);

	UFUNCTION(BlueprintImplementableEvent)
	void OnConfirmTriggered(const FInputActionValue& Value);

	UFUNCTION(BlueprintImplementableEvent)
	void OnCancelTriggered(const FInputActionValue& Value);

	UFUNCTION(BlueprintImplementableEvent)
	void OnTabTriggered(const FInputActionValue& Value);

	UFUNCTION(BlueprintImplementableEvent)
	void OnAnyInputTriggered(const FInputActionValue& Value);

	virtual void NativeOnLeftClickTriggered(const FInputActionValue& Value) {};
	virtual void NativeOnMiddleClickTriggered(const FInputActionValue& Value) {};
	virtual void NativeOnRightClickTriggered(const FInputActionValue& Value) {};
	virtual void NativeOnMouseWheelTriggered(const FInputActionValue& Value) {};
	virtual void NativeOnNavigateTriggered(const FInputActionValue& Value) {};
	virtual void NativeOnConfirmTriggered(const FInputActionValue& Value) {};
	virtual void NativeOnCancelTriggered(const FInputActionValue& Value) {};
	virtual void NativeOnTabTriggered(const FInputActionValue& Value) {};
	virtual void NativeOnAnyInputTriggered(const FInputActionValue& Value) {};

	FORCEINLINE const FGameplayTag& GetOwningLayerName() const { return OwningLayerName; }
};
