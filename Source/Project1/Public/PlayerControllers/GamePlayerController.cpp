// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayerController.h"
#include "Kismet/GameplayStatics.h"

void AGamePlayerController::ReceiveAnyKeyInput(const FKey& Key, EInputEvent InputEvent)
{
	Super::ReceiveAnyKeyInput(Key, InputEvent);

	if (Key == EKeys::I)
	{
		if (InputEvent == IE_Pressed)
		{
			UGameplayStatics::OpenLevel(this, FName(TEXT("TitleScreenMap")));
		}
	}
}
