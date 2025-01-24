// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleScreenPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "GameViewportClients/Project1GameViewportClientBase.h"

void ATitleScreenPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Get project1 game viewport client
	Project1GameViewportClient = CastChecked<UProject1GameViewportClientBase>(UGameplayStatics::GetGameInstance(this)->GetGameViewportClient());

	// Bind to on input device changed events
	OnMouseMovedDelegateHandle = Project1GameViewportClient->OnMouseMovedDelegate.AddWeakLambda(this,
		[this](const FVector2D& NewMousePosition, const FVector2D& OldMousePosition, const FVector2D& MouseMoveDelta) {
			SetMouseCursorVisibility(EMouseCursorVisibility::Visible, bLockMouseToViewportWhenShown, bCenterMouseInViewportWhenShown);
		});

	// TODO: Hide cursor on any keyboard or gamepad input
}

void ATitleScreenPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	// Unbind from game viewport client events
	Project1GameViewportClient->OnMouseMovedDelegate.Remove(OnMouseMovedDelegateHandle);
	OnMouseMovedDelegateHandle.Reset();
}
