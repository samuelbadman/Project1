// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleScreenPlayerController.h"
#include "UserWidgets/Project1UserWidgetBase.h"
#include "Kismet/GameplayStatics.h"

void ATitleScreenPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Create title screen widget
	TitleScreenWidget = CreateWidget<UProject1UserWidgetBase>(this, TitleScreenWidgetClass);
#if WITH_EDITOR
	if (!IsValid(TitleScreenWidget))
	{
		UE_LOG(LogTemp, Error, TEXT("TitleScreenWidget failed to create. Is a class set to create for the title screen widget in the title screen player controller?"));
		return;
	}
#endif
	TitleScreenWidget->AddToViewport();
}

void ATitleScreenPlayerController::ReceiveAnyKeyInput(const FKey& Key, EInputEvent InputEvent)
{
	Super::ReceiveAnyKeyInput(Key, InputEvent);

	if (Key == EKeys::I)
	{
		if (InputEvent == IE_Pressed)
		{
			UGameplayStatics::OpenLevel(this, FName(TEXT("DevelopmentMap")));
		}
	}
}
