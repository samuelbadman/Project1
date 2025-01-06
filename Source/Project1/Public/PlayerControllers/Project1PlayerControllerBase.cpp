// Fill out your copyright notice in the Description page of Project Settings.


#include "Project1PlayerControllerBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameInstances/Project1GameInstanceBase.h"
#include "ProjectInput/InputKeyStateController.h"
#include "HUDs/Project1HUDBase.h"

void AProject1PlayerControllerBase::SetMouseCursorVisibility(EMouseCursorVisibility NewVisibility, bool LockMouseCursorToViewportWhenVisible, bool CenterCursorInViewportOnBecomeVisible)
{
	FInputModeGameAndUI InputModeGameAndUI{};
	InputModeGameAndUI.SetHideCursorDuringCapture(false);

	switch (NewVisibility)
	{
	case EMouseCursorVisibility::Visible:
		InputModeGameAndUI.SetLockMouseToViewportBehavior((LockMouseCursorToViewportWhenVisible) ? EMouseLockMode::LockAlways : EMouseLockMode::DoNotLock);

		SetShowMouseCursor(true);

		if (CenterCursorInViewportOnBecomeVisible)
		{
			CenterMouseCursorInViewport();
		}

		break;

	case EMouseCursorVisibility::Hidden:
		InputModeGameAndUI.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);

		SetShowMouseCursor(false);

		break;
	}

	SetInputMode(InputModeGameAndUI);

	FSlateApplication::Get().QueryCursor();
}

void AProject1PlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();

	// Get game instance reference as project game instance to access input key state manager object
	ProjectGameInstance = CastChecked<UProject1GameInstanceBase>(UGameplayStatics::GetGameInstance(this));

	// Get HUD reference as project HUD reference to forward legacy player inputs to for UI input
	Project1HUD = CastChecked<AProject1HUDBase>(GetHUD());

	// Set default mouse cursor visibility
	SetMouseCursorVisibility(DefaultMouseCursorVisibility, DefaultLockMouseCursorToViewportWhenVisible, DefaultCenterCursorInViewportOnBecomeVisible);
}

void AProject1PlayerControllerBase::CenterMouseCursorInViewport()
{
	int32 ViewportX{ 0 }, ViewportY{ 0 };
	GetViewportSize(ViewportX, ViewportY);
	SetMouseLocation(ViewportX / 2, ViewportY / 2);
}
