// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserWidgets/Project1UserWidgetBase.h"
#include "HelperObjects/WidgetLayerClassASyncLoadHandle.h"
#include "GameplayTagContainer.h"
#include "LayerUserWidgetBase.generated.h"

class UScreenUserWidgetBase;
class UPanelWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnContentPushedToLayerDelegateSignature, UScreenUserWidgetBase*, Widget);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnContentPoppedFromLayerDelegateSignature, UScreenUserWidgetBase*, Widget);

/**
 *
 */
UCLASS()
class PROJECT1_API ULayerUserWidgetBase : public UProject1UserWidgetBase
{
	GENERATED_BODY()

private:
	UPROPERTY(BlueprintAssignable)
	FOnContentPushedToLayerDelegateSignature OnContentPushedToLayerDelegate{};

	UPROPERTY(BlueprintAssignable)
	FOnContentPoppedFromLayerDelegateSignature OnContentPoppedFromLayerDelegate{};

	FGameplayTag LayerName{};

	UPROPERTY()
	TArray<TObjectPtr<UScreenUserWidgetBase>> WidgetStack{};
	
	UPROPERTY()
	TArray<TObjectPtr<UWidgetLayerClassASyncLoadHandle>> PushedContentClassASyncLoadHandles{};

public:
	UFUNCTION(BlueprintImplementableEvent)
	UPanelWidget* GetPanelWidget() const;

	// Do not call. Called when registering the layer with a primary layout widget.
	void SetLayerName(const FGameplayTag& Name);
	// Pushed widget class is loaded asynchronously before being shown on screen. The layer will not be in its final state immediately after calling this function
	void PushContent(const TSoftClassPtr<UScreenUserWidgetBase>& WidgetClass, const TObjectPtr<UScreenWidgetLoadPayloadBase> LoadPayloadObject = nullptr);
	void PopContent();
	TObjectPtr<UScreenUserWidgetBase> Peek() const;
	void CollapseTop();
	void ShowTop();
	bool IsEmpty() const;

	void OnLoadedPushedContentWidgetClass(TObjectPtr<UWidgetLayerClassASyncLoadHandle> Handle);
};
