// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleScreenHUD.h"
#include "UserWidgets/TitleScreenMasterUserWidget.h"

void ATitleScreenHUD::BeginPlay()
{
	Super::BeginPlay();

	// Create title screen master widget
	TitleScreenMasterWidget = CreateWidget<UTitleScreenMasterUserWidget>(GetOwningPlayerController(), TitleScreenMasterWidgetClass);
#if WITH_EDITOR
	if (!IsValid(TitleScreenMasterWidget))
	{
		UE_LOG(LogTemp, Error, TEXT("TitleScreenMasterWidget failed to create. Is a class set to create for the title screen widget in the title screen player controller?"));
		return;
	}
#endif
	TitleScreenMasterWidget->AddToViewport();
}
