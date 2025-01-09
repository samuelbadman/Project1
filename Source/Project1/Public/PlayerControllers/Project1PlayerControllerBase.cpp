// Fill out your copyright notice in the Description page of Project Settings.


#include "Project1PlayerControllerBase.h"

void AProject1PlayerControllerBase::SetMouseCursorVisibility(EMouseCursorVisibility NewVisibility, bool LockMouseCursorToViewportWhenVisible, bool CenterCursorInViewportOnBecomeVisible)
{
	switch (NewVisibility)
	{
	case EMouseCursorVisibility::Visible:
	{
		SetShowMouseCursor(true);

		if (CenterCursorInViewportOnBecomeVisible)
		{
			CenterMouseCursorInViewport();
		}

		FInputModeGameAndUI InputModeGameAndUI{};
		InputModeGameAndUI.SetHideCursorDuringCapture(false);
		InputModeGameAndUI.SetLockMouseToViewportBehavior((LockMouseCursorToViewportWhenVisible) ? EMouseLockMode::LockAlways : EMouseLockMode::DoNotLock);
		SetInputMode(InputModeGameAndUI);

		break;
	}

	case EMouseCursorVisibility::Hidden:
	{
		SetShowMouseCursor(false);

		FInputModeGameOnly InputModeGameOnly{};
		InputModeGameOnly.SetConsumeCaptureMouseDown(false);
		SetInputMode(InputModeGameOnly);

		break;
	}
	}

	OnMouseCursorVisibilityChanged(NewVisibility);
}

void AProject1PlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();

	// Set default mouse cursor visibility
	SetMouseCursorVisibility(DefaultMouseCursorVisibility, DefaultLockMouseCursorToViewportWhenVisible, DefaultCenterCursorInViewportOnBecomeVisible);
}

void AProject1PlayerControllerBase::CenterMouseCursorInViewport()
{
	int32 ViewportX{ 0 }, ViewportY{ 0 };
	GetViewportSize(ViewportX, ViewportY);
	SetMouseLocation(ViewportX / 2, ViewportY / 2);
}
