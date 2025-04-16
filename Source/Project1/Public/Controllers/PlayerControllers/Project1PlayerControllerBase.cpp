// Fill out your copyright notice in the Description page of Project Settings.


#include "Project1PlayerControllerBase.h"
#include "Components/ActorComponents/UIInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

AProject1PlayerControllerBase::AProject1PlayerControllerBase()
	:
	UIInputComponent(CreateDefaultSubobject<UUIInputComponent>(FName(TEXT("UIInputComponent"))))
{
}

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

EMouseCursorVisibility AProject1PlayerControllerBase::GetMouseCursorVisibility() const
{
	return (IsMouseCursorVisible()) ? EMouseCursorVisibility::Visible : EMouseCursorVisibility::Hidden;
}

FVector2D AProject1PlayerControllerBase::GetMouseCursorPosition() const
{
	FVector2D MousePosition;
	GetMousePosition(MousePosition.X, MousePosition.Y);
	return MousePosition;
}

void AProject1PlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();

	// Store enhanced input local player subsystem
	EnhancedInputLocalPlayerSubsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();

	// Set default mouse cursor visibility
	SetMouseCursorVisibility(DefaultMouseCursorVisibility, DefaultLockMouseCursorToViewportWhenVisible, DefaultCenterCursorInViewportOnBecomeVisible);
}

void AProject1PlayerControllerBase::OnMouseCursorVisibilityChanged(EMouseCursorVisibility NewVisibility)
{
	MouseCursorVisibilityChanged.Broadcast(NewVisibility, GetMouseCursorPosition());
}

void AProject1PlayerControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();

	UIInputComponent->SetupUIInputComponent(CastChecked<UEnhancedInputComponent>(InputComponent));
}

void AProject1PlayerControllerBase::CenterMouseCursorInViewport()
{
	int32 ViewportX{ 0 }, ViewportY{ 0 };
	GetViewportSize(ViewportX, ViewportY);
	SetMouseLocation(ViewportX / 2, ViewportY / 2);
}
