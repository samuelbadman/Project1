// Fill out your copyright notice in the Description page of Project Settings.


#include "Project1HUDBase.h"
#include "UserWidgets/PrimaryLayouts/PrimaryLayoutUserWidgetBase.h"

void AProject1HUDBase::PushContentToPrimaryLayoutLayer(const FGameplayTag& LayerName, const TSoftClassPtr<UScreenUserWidgetBase>& WidgetClass)
{
	PrimaryLayoutWidget->PushContentToLayer(LayerName, WidgetClass);
}

void AProject1HUDBase::PopContentFromPrimaryLayoutLayer(const FGameplayTag& LayerName)
{
	PrimaryLayoutWidget->PopContentFromLayer(LayerName);
}

ULayerUserWidgetBase* AProject1HUDBase::GetRegisteredPrimaryLayoutLayer(const FGameplayTag& LayerName)
{
	return PrimaryLayoutWidget->GetRegisteredLayer(LayerName);
}

void AProject1HUDBase::SetActiveInputPrimaryLayoutLayer(const FGameplayTag& LayerName)
{
	PrimaryLayoutWidget->SetActiveInputLayer(LayerName);
}

const FGameplayTag& AProject1HUDBase::GetActiveInputPrimaryLayoutLayerName() const
{
	return PrimaryLayoutWidget->GetActiveInputLayerName();
}

bool AProject1HUDBase::IsContentOnTopOfPrimaryLayoutLayer(const FGameplayTag& LayerName, TObjectPtr<UScreenUserWidgetBase> Widget) const
{
	return PrimaryLayoutWidget->IsContentOnTopOfLayer(LayerName, Widget);
}

void AProject1HUDBase::BeginPlay()
{
	Super::BeginPlay();

	// Create primary layout widget, cache it and add it to the viewport
	PrimaryLayoutWidget = CreateWidget<UPrimaryLayoutUserWidgetBase>(GetOwningPlayerController(), PrimaryLayoutWidgetClass);
#if WITH_EDITOR
	if (!IsValid(PrimaryLayoutWidget))
	{
		UE_LOG(LogTemp, Error, TEXT("PrimaryLayoutWidget failed to create. Is a class set in the HUD blueprint?"));
		return;
	}
#endif
	PrimaryLayoutWidget->AddToViewport();
}
