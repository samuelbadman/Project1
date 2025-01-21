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
	PreviousActiveInputLayerName = ActiveInputLayerName;
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

void UPrimaryLayoutUserWidgetBase::RouteOnMouseMoved(const FVector2D& NewMousePosition, const FVector2D& OldMousePosition, const FVector2D& MouseMoveDelta)
{
	const TObjectPtr<ULayerUserWidgetBase> ActiveInputLayer = GetActiveInputLayer();
	if (IsValid(ActiveInputLayer))
	{
		ActiveInputLayer->ReceiveOnMouseMoved(NewMousePosition, OldMousePosition, MouseMoveDelta);
	}
}

void UPrimaryLayoutUserWidgetBase::RouteOnLeftClickTriggered(const FInputActionValue& Value)
{
	const TObjectPtr<ULayerUserWidgetBase> ActiveInputLayer = GetActiveInputLayer();
	if (IsValid(ActiveInputLayer))
	{
		ActiveInputLayer->ReceiveOnLeftClickTriggered(Value);
	}
}

void UPrimaryLayoutUserWidgetBase::RouteOnMiddleClickTriggered(const FInputActionValue& Value)
{
	const TObjectPtr<ULayerUserWidgetBase> ActiveInputLayer = GetActiveInputLayer();
	if (IsValid(ActiveInputLayer))
	{
		ActiveInputLayer->ReceiveOnMiddleClickTriggered(Value);
	}
}

void UPrimaryLayoutUserWidgetBase::RouteOnRightClickTriggered(const FInputActionValue& Value)
{
	const TObjectPtr<ULayerUserWidgetBase> ActiveInputLayer = GetActiveInputLayer();
	if (IsValid(ActiveInputLayer))
	{
		ActiveInputLayer->ReceiveOnRightClickTriggered(Value);
	}
}

void UPrimaryLayoutUserWidgetBase::RouteOnMouseWheelTriggered(const FInputActionValue& Value)
{
	const TObjectPtr<ULayerUserWidgetBase> ActiveInputLayer = GetActiveInputLayer();
	if (IsValid(ActiveInputLayer))
	{
		ActiveInputLayer->ReceiveOnMouseWheelTriggered(Value);
	}
}

void UPrimaryLayoutUserWidgetBase::RouteOnNavigateTriggered(const FInputActionValue& Value)
{
	const TObjectPtr<ULayerUserWidgetBase> ActiveInputLayer = GetActiveInputLayer();
	if (IsValid(ActiveInputLayer))
	{
		ActiveInputLayer->ReceiveOnNavigateTriggered(Value);
	}
}

void UPrimaryLayoutUserWidgetBase::RouteOnNavigateNoMoveTriggered(const FInputActionValue& Value)
{
	const TObjectPtr<ULayerUserWidgetBase> ActiveInputLayer = GetActiveInputLayer();
	if (IsValid(ActiveInputLayer))
	{
		ActiveInputLayer->ReceiveOnNavigateNoMoveTriggered(Value);
	}
}

void UPrimaryLayoutUserWidgetBase::RouteOnNavigateNoMoveNoRepeatTriggered(const FInputActionValue& Value)
{
	const TObjectPtr<ULayerUserWidgetBase> ActiveInputLayer = GetActiveInputLayer();
	if (IsValid(ActiveInputLayer))
	{
		ActiveInputLayer->ReceiveOnNavigateNoMoveNoRepeatTriggered(Value);
	}
}

void UPrimaryLayoutUserWidgetBase::RouteOnConfirmTriggered(const FInputActionValue& Value)
{
	const TObjectPtr<ULayerUserWidgetBase> ActiveInputLayer = GetActiveInputLayer();
	if (IsValid(ActiveInputLayer))
	{
		ActiveInputLayer->ReceiveOnConfirmTriggered(Value);
	}
}

void UPrimaryLayoutUserWidgetBase::RouteOnCancelTriggered(const FInputActionValue& Value)
{
	const TObjectPtr<ULayerUserWidgetBase> ActiveInputLayer = GetActiveInputLayer();
	if (IsValid(ActiveInputLayer))
	{
		ActiveInputLayer->ReceiveOnCancelTriggered(Value);
	}
}

void UPrimaryLayoutUserWidgetBase::RouteOnTabTriggered(const FInputActionValue& Value)
{
	const TObjectPtr<ULayerUserWidgetBase> ActiveInputLayer = GetActiveInputLayer();
	if (IsValid(ActiveInputLayer))
	{
		ActiveInputLayer->ReceiveOnTabTriggered(Value);
	}
}

void UPrimaryLayoutUserWidgetBase::RouteOnAnyInputTriggered(const FInputActionValue& Value)
{
	const TObjectPtr<ULayerUserWidgetBase> ActiveInputLayer = GetActiveInputLayer();
	if (IsValid(ActiveInputLayer))
	{
		ActiveInputLayer->ReceiveOnAnyInputTriggered(Value);
	}
}

TObjectPtr<ULayerUserWidgetBase> UPrimaryLayoutUserWidgetBase::GetActiveInputLayer()
{
	TObjectPtr<ULayerUserWidgetBase>* const pLayer{ Layers.Find(ActiveInputLayerName) };
	
	if (!pLayer)
	{
		return nullptr;
	}

	return (*pLayer);
}
