// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetLayerClassASyncLoadHandle.h"
#include "UserWidgets/Layers/LayerUserWidgetBase.h"
#include "Engine/StreamableManager.h"

void UWidgetLayerClassASyncLoadHandle::OnLoadedClass()
{
	WidgetLayer->OnLoadedPushedContentWidgetClass(this);
}
