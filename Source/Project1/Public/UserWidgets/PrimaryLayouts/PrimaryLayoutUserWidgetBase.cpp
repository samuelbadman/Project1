// Fill out your copyright notice in the Description page of Project Settings.


#include "PrimaryLayoutUserWidgetBase.h"
#include "UserWidgets/Layers/LayerUserWidgetBase.h"

bool UPrimaryLayoutUserWidgetBase::RegisterLayer(const FGameplayTag& LayerName, ULayerUserWidgetBase* LayerWidget)
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

void UPrimaryLayoutUserWidgetBase::PushContentToLayer(const FGameplayTag& LayerName, const TSoftClassPtr<UScreenUserWidgetBase>& WidgetClass)
{
	TObjectPtr<ULayerUserWidgetBase>* const pLayer{ Layers.Find(LayerName) };

	if (pLayer)
	{
		(*pLayer)->PushContent(WidgetClass);
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

void UPrimaryLayoutUserWidgetBase::SetActiveInputLayer(const FGameplayTag& LayerName)
{
	ActiveInputLayerName = LayerName;
}

bool UPrimaryLayoutUserWidgetBase::IsContentOnTopOfLayer(const FGameplayTag& LayerName, TObjectPtr<UScreenUserWidgetBase> Widget)
{
	TObjectPtr<ULayerUserWidgetBase>* const pLayer{ Layers.Find(LayerName) };

	if (!pLayer)
	{
		return false;
	}

	return (Widget == (*pLayer)->Peek());
}

void UPrimaryLayoutUserWidgetBase::RouteInputToActiveInputLayer(const FKey& Key, const EInputEvent Event)
{
	TObjectPtr<ULayerUserWidgetBase>* const pActiveInputLayer{ Layers.Find(ActiveInputLayerName) };

	if (!pActiveInputLayer)
	{
		// A layer with the name active input layer name is set to has not been registered with the primary layout widget
		return;
	}

	(*pActiveInputLayer)->ReceiveInput(Key, Event);
}
