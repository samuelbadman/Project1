// Fill out your copyright notice in the Description page of Project Settings.


#include "Project1PlayerControllerBase.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

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

void AProject1PlayerControllerBase::AddConfirmModalInputMappingContext()
{
	const TObjectPtr<UEnhancedInputLocalPlayerSubsystem> EnhancedInputLocalPlayerSubsystem = GetEnhancedInputLocalPlayerSubsystem();
	EnhancedInputLocalPlayerSubsystem->AddMappingContext(ConfirmModalInputMappingContext, ConfirmModalInputPriority);
}

void AProject1PlayerControllerBase::RemoveConfirmModalInputMappingContext()
{
	const TObjectPtr<UEnhancedInputLocalPlayerSubsystem> EnhancedInputLocalPlayerSubsystem = GetEnhancedInputLocalPlayerSubsystem();
	EnhancedInputLocalPlayerSubsystem->RemoveMappingContext(ConfirmModalInputMappingContext);
}

void AProject1PlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();

	// Set default mouse cursor visibility
	SetMouseCursorVisibility(DefaultMouseCursorVisibility, DefaultLockMouseCursorToViewportWhenVisible, DefaultCenterCursorInViewportOnBecomeVisible);
}

TObjectPtr<UEnhancedInputLocalPlayerSubsystem> AProject1PlayerControllerBase::GetEnhancedInputLocalPlayerSubsystem() const
{
	if (const TObjectPtr<ULocalPlayer> LocalPlayer = GetLocalPlayer())
	{
		return LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	}
	return nullptr;
}

void AProject1PlayerControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();

	const TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent{ CastChecked<UEnhancedInputComponent>(InputComponent) };

	EnhancedInputComponent->BindAction(ConfirmModalConfirmInputAction, ETriggerEvent::Triggered, this, &AProject1PlayerControllerBase::OnConfirmModalConfirmTriggered);
	EnhancedInputComponent->BindAction(ConfirmModalNavigateInputAction, ETriggerEvent::Triggered, this, &AProject1PlayerControllerBase::OnConfirmModalNavigateTriggered);
}

void AProject1PlayerControllerBase::CenterMouseCursorInViewport()
{
	int32 ViewportX{ 0 }, ViewportY{ 0 };
	GetViewportSize(ViewportX, ViewportY);
	SetMouseLocation(ViewportX / 2, ViewportY / 2);
}

void AProject1PlayerControllerBase::OnConfirmModalConfirmTriggered(const FInputActionValue& Value)
{
	ConfirmModalConfirmTriggered.Broadcast(Value);
}

void AProject1PlayerControllerBase::OnConfirmModalNavigateTriggered(const FInputActionValue& Value)
{
	ConfirmModalNavigateTriggered.Broadcast(Value);
}
