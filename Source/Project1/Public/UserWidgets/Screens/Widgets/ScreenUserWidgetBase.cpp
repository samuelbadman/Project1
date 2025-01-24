// Fill out your copyright notice in the Description page of Project Settings.


#include "ScreenUserWidgetBase.h"
#include "UserWidgets/Layers/LayerUserWidgetBase.h"
#include "HUDs/Project1HUDBase.h"
#include "Kismet/GameplayStatics.h"

void UScreenUserWidgetBase::SetOwningLayer(TObjectPtr<ULayerUserWidgetBase> Layer)
{
	OwningLayer = Layer;
}

const FGameplayTag& UScreenUserWidgetBase::GetOwningLayerName() const
{
	return OwningLayer->GetLayerName();
}

bool UScreenUserWidgetBase::CanReceiveInput() const
{
	// A screen widget can only receive input if is on the top of its owning layer's widget stack and there is not another screen on a widget layer with a higher priority than
	// the screen widget's owning layer's priority
	return ((IsTopOfOwningLayer()) &&
		(!IsInputBlockedByHigherLayer()));
}

bool UScreenUserWidgetBase::IsTopOfOwningLayer() const
{
	return (OwningLayer->Peek() == this);
}

bool UScreenUserWidgetBase::IsInputBlockedByHigherLayer() const
{
	return Project1HUD->DoesPrimaryLayoutWidgetLayerBlockContentInput(OwningLayer->GetLayerPriority());
}

void UScreenUserWidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	Project1HUD = CastChecked<AProject1HUDBase>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
}
