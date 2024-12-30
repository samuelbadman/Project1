// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleScreenHUD.h"
#include "UserWidgets/PrimaryLayouts/PrimaryLayoutUserWidgetBase.h"

void ATitleScreenHUD::BeginPlay()
{
	Super::BeginPlay();

	// Create title screen primary layout widget, cache it and add it to the viewport
	TitleScreenPrimaryLayoutWidget = CreateWidget<UPrimaryLayoutUserWidgetBase>(GetOwningPlayerController(), TitleScreenPrimaryLayoutWidgetClass);
#if WITH_EDITOR
	if (!IsValid(TitleScreenPrimaryLayoutWidget))
	{
		UE_LOG(LogTemp, Error, TEXT("TitleScreenPrimaryLayoutWidget failed to create. Is a class set in the title screen HUD blueprint?"));
		return;
	}
#endif
	TitleScreenPrimaryLayoutWidget->AddToViewport();
}
