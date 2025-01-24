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
