// Fill out your copyright notice in the Description page of Project Settings.


#include "PrimaryLayoutUserWidgetBase.h"
#include "UMG/Layers/LayerUserWidgetBase.h"

bool UPrimaryLayoutUserWidgetBase::RegisterLayer(const FGameplayTag& LayerName, int32 InLayerPriority, ULayerUserWidgetBase* LayerWidget)
{
	if (!IsValid(LayerWidget))
	{
		return false;
	}

	if (Layers.Contains(LayerName))
	{
		return false;
	}

	TObjectPtr<ULayerUserWidgetBase>& RegisteredLayer{ Layers.Add(LayerName, LayerWidget) };
	RegisteredLayer->SetLayerName(LayerName);
	RegisteredLayer->SetLayerPriority(InLayerPriority);

	return true;
}

bool UPrimaryLayoutUserWidgetBase::UnregisterLayer(const FGameplayTag& LayerName)
{
	TObjectPtr<ULayerUserWidgetBase>* const pLayer{ Layers.Find(LayerName) };

	if (pLayer)
	{
		(*pLayer)->RemoveFromParent();
	}

	return (Layers.Remove(LayerName) > 0);
}

void UPrimaryLayoutUserWidgetBase::PushContentToLayer(
	const FGameplayTag& LayerName, 
	const TSoftClassPtr<UScreenUserWidgetBase>& WidgetClass,
	UScreenWidgetLoadPayloadBase* const LoadPayloadObject
)
{
	TObjectPtr<ULayerUserWidgetBase>* const pLayer{ Layers.Find(LayerName) };

	if (pLayer)
	{
		(*pLayer)->PushContent(WidgetClass, LoadPayloadObject);
	}
}

void UPrimaryLayoutUserWidgetBase::PopContentFromLayer(const FGameplayTag& LayerName)
{
	TObjectPtr<ULayerUserWidgetBase>* const pLayer{ Layers.Find(LayerName) };

	if (pLayer)
	{
		(*pLayer)->PopContent();
	}
}

ULayerUserWidgetBase* UPrimaryLayoutUserWidgetBase::GetRegisteredLayer(const FGameplayTag& LayerName)
{
	TObjectPtr<ULayerUserWidgetBase>* const pLayer{ Layers.Find(LayerName) };

	if (!pLayer)
	{
		return nullptr;
	}

	return (*pLayer);
}

bool UPrimaryLayoutUserWidgetBase::DoesLayerBlockContentInput(const int32 ContentLayerPriority) const
{
	// For each layer
	for (const TPair<FGameplayTag, TObjectPtr<ULayerUserWidgetBase>>& Pair : Layers)
	{
		// Does the layer have a higher priority
		// Layers with the same priority will not block input
		if (Pair.Value->GetLayerPriority() > ContentLayerPriority)
		{
			// Should the layer block input
			if (Pair.Value->ShouldBlockLowerPriorityLayerInput())
			{
				// Block input
				return true;
			}
		}
	}

	// No layer blocked input
	return false;
}
