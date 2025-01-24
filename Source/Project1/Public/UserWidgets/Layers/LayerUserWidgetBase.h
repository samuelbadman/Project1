// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserWidgets/Project1UserWidgetBase.h"
#include "HelperObjects/WidgetLayerClassASyncLoadHandle.h"
#include "GameplayTagContainer.h"
#include "LayerUserWidgetBase.generated.h"

class UScreenUserWidgetBase;
class UPanelWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnContentPushedToLayerDelegate, UScreenUserWidgetBase*, Widget);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnContentPoppedFromLayerDelegate, UScreenUserWidgetBase*, Widget);

/**
 *
 */
UCLASS()
class PROJECT1_API ULayerUserWidgetBase : public UProject1UserWidgetBase
{
	GENERATED_BODY()

private:
	UPROPERTY(BlueprintAssignable, meta = (DisplayName = "On Content Pushed To Layer"))
	FOnContentPushedToLayerDelegate ContentPushedToLayer{};

	UPROPERTY(BlueprintAssignable, meta = (DisplayName = "On Content Popped From Layer"))
	FOnContentPoppedFromLayerDelegate ContentPoppedFromLayer{};

	FGameplayTag LayerName{};
	// Higher priorities are more important. 1 has more priority than 0
	int32 LayerPriority{ 0 };

	UPROPERTY()
	TArray<TObjectPtr<UScreenUserWidgetBase>> WidgetStack{};
	
	UPROPERTY()
	TArray<TObjectPtr<UWidgetLayerClassASyncLoadHandle>> PushedContentClassASyncLoadHandles{};

public:
	UFUNCTION(BlueprintImplementableEvent)
	UPanelWidget* GetPanelWidget() const;

	// Do not call. Called when registering the layer with a primary layout widget.
	void SetLayerName(const FGameplayTag& Name) { LayerName = Name; }
	void SetLayerPriority(const int32 InPriority) { LayerPriority = InPriority; }

	// Pushed widget class is loaded asynchronously before being shown on screen. The layer will not be in its final state immediately after calling this function
	void PushContent(const TSoftClassPtr<UScreenUserWidgetBase>& WidgetClass, const TObjectPtr<UScreenWidgetLoadPayloadBase> LoadPayloadObject = nullptr);
	void PopContent();
	TObjectPtr<UScreenUserWidgetBase> Peek() const;
	void CollapseTop();
	void ShowTop();
	bool IsEmpty() const;
	bool IsContentTop(TObjectPtr<UScreenUserWidgetBase> Content) const;
	bool ShouldBlockLowerPriorityLayerInput() const;

	void OnLoadedPushedContentWidgetClass(TObjectPtr<UWidgetLayerClassASyncLoadHandle> Handle);

	FORCEINLINE const FGameplayTag& GetLayerName() const { return LayerName; }
	FORCEINLINE int32 GetLayerPriority() const { return LayerPriority; }
};
