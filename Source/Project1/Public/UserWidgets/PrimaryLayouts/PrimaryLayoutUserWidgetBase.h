// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserWidgets/Project1UserWidgetBase.h"
#include "GameplayTagContainer.h"
#include "PrimaryLayoutUserWidgetBase.generated.h"

class ULayerUserWidgetBase;
class UScreenUserWidgetBase;
struct FInputActionValue;

/**
 * 
 */
UCLASS()
class PROJECT1_API UPrimaryLayoutUserWidgetBase : public UProject1UserWidgetBase
{
	GENERATED_BODY()
	
private:
	TMap<FGameplayTag, TObjectPtr<ULayerUserWidgetBase>> Layers{};
	FGameplayTag ActiveInputLayerName{};

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

	UFUNCTION(BlueprintCallable)
	void SetActiveInputLayer(const FGameplayTag& LayerName);

	bool IsContentOnTopOfLayer(const FGameplayTag& LayerName, TObjectPtr<UScreenUserWidgetBase> Widget);

	void RouteOnMouseMoved(const FVector2D& NewMousePosition, const FVector2D& OldMousePosition, const FVector2D& MouseMoveDelta);
	void RouteOnLeftClickTriggered(const FInputActionValue& Value);
	void RouteOnMiddleClickTriggered(const FInputActionValue& Value);
	void RouteOnRightClickTriggered(const FInputActionValue& Value);
	void RouteOnMouseWheelTriggered(const FInputActionValue& Value);
	void RouteOnNavigateTriggered(const FInputActionValue& Value);
	void RouteOnConfirmTriggered(const FInputActionValue& Value);
	void RouteOnCancelTriggered(const FInputActionValue& Value);
	void RouteOnTabTriggered(const FInputActionValue& Value);
	void RouteOnAnyInputTriggered(const FInputActionValue& Value);

private:
	TObjectPtr<ULayerUserWidgetBase> GetActiveInputLayer();
};
