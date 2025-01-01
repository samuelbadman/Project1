// Fill out your copyright notice in the Description page of Project Settings.


#include "Project1HUDBase.h"
#include "UserWidgets/PrimaryLayouts/PrimaryLayoutUserWidgetBase.h"

void AProject1HUDBase::ReceiveRawPlayerInput(const FKey& Key, EInputEvent InputEvent)
{
	PrimaryLayoutWidget->ReceiveRawInput(Key, InputEvent);
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
