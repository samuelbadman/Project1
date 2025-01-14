// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleScreenPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "GameViewportClients/Project1GameViewportClientBase.h"

void ATitleScreenPlayerController::BeginPlay()
{
	Super::BeginPlay();

	CastChecked<UProject1GameViewportClientBase>(UGameplayStatics::GetGameInstance(this)->GetGameViewportClient())->GetOnInputDeviceChangedDelegate().AddLambda(
		[this](bool UsingGamepad) {
			SetMouseCursorVisibility((UsingGamepad) ? EMouseCursorVisibility::Hidden : EMouseCursorVisibility::Visible, false, true);
		});
}
