// Fill out your copyright notice in the Description page of Project Settings.


#include "Project1ButtonBase.h"
#include "Components/Border.h"
#include "Components/BorderSlot.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerControllers/Project1PlayerControllerBase.h"
#include "GameViewportClients/Project1GameViewportClientBase.h"

void UProject1ButtonBase::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (const TObjectPtr<UBorder> Border = GetBorder())
	{
		Border->SetBrush(NormalBrush);

		CastChecked<UBorderSlot>(Border->GetSlots()[0])->SetPadding(ContentPadding);
	}
}

void UProject1ButtonBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Project1PlayerController = CastChecked<AProject1PlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));
	Project1GameViewportClient = CastChecked<UProject1GameViewportClientBase>(UGameplayStatics::GetGameInstance(this)->GetGameViewportClient());

	if (bStartWithMouseInputsActivated)
	{
		ActivateMouseInputs();
	}
}

void UProject1ButtonBase::NativeDestruct()
{
	if (bMouseInputsActivated)
	{
		DeactivateMouseInputs();
	}

	Super::NativeDestruct();
}

void UProject1ButtonBase::ActivateMouseInputs()
{
	OnMouseCursorVisibilityChangedDelegateHandle = Project1PlayerController->MouseCursorVisibilityChanged.AddUObject(this, &UProject1ButtonBase::OnMouseCursorVisibilityChanged);
	OnMouseMovedDelegateHandle = Project1GameViewportClient->MouseMoved.AddUObject(this, &UProject1ButtonBase::OnMouseMoved);
	OnInputKeyDelegateHandle = Project1GameViewportClient->OnInputKey.AddUObject(this, &UProject1ButtonBase::OnInputKey);
	bMouseInputsActivated = true;
}

void UProject1ButtonBase::DeactivateMouseInputs()
{
	Project1PlayerController->MouseCursorVisibilityChanged.Remove(OnMouseCursorVisibilityChangedDelegateHandle);
	OnMouseCursorVisibilityChangedDelegateHandle.Reset();

	Project1GameViewportClient->MouseMoved.Remove(OnMouseMovedDelegateHandle);
	OnMouseMovedDelegateHandle.Reset();

	Project1GameViewportClient->OnInputKey.Remove(OnInputKeyDelegateHandle);
	OnInputKeyDelegateHandle.Reset();

	bMouseInputsActivated = false;
}

void UProject1ButtonBase::MakeHovered()
{
	if (bHovered)
	{
		return;
	}

	GetBorder()->SetBrush(HoveredBrush);

	bHovered = true;
	OnHovered.Broadcast(this);
}

void UProject1ButtonBase::MakeUnhovered()
{
	if (!bHovered)
	{
		return;
	}

	GetBorder()->SetBrush(NormalBrush);

	bHovered = false;
	OnUnhovered.Broadcast(this);
}

void UProject1ButtonBase::PressButton()
{
	OnPressed.Broadcast(this);
}

void UProject1ButtonBase::OnMouseCursorVisibilityChanged(EMouseCursorVisibility NewVisibility, const FVector2D& MousePosition)
{
	// Generate mouse enter/leave events
	const bool bNewCursorOver{ IsMouseCursorOverWidgetGeometry(MousePosition) };

	if ((NewVisibility == EMouseCursorVisibility::Visible) &&
		(bNewCursorOver))
	{
		OnMouseCursorEntered();
	}
	else if ((NewVisibility == EMouseCursorVisibility::Hidden) &&
		(bNewCursorOver))
	{
		OnMouseCursorLeft();
	}
}

void UProject1ButtonBase::OnMouseMoved(const FVector2D& NewMousePosition, const FVector2D& OldMousePosition, const FVector2D& MouseMoveDelta)
{
	// Only attempt to update hovered state when the cursor is shown
	if (!Project1PlayerController->IsMouseCursorVisible())
	{
		return;
	}

	if (IsMouseCursorOverWidgetGeometry(NewMousePosition))
	{
		if (!bCursorOver)
		{
			OnMouseCursorEntered();
		}
	}
	else
	{
		if (bCursorOver)
		{
			OnMouseCursorLeft();
		}
	}
}

void UProject1ButtonBase::OnInputKey(const FInputKeyEventArgs& EventArgs)
{
	// Only accept click events when the mouse cursor is visible
	if (!Project1PlayerController->IsMouseCursorVisible())
	{
		return;
	}

	// Generate click event
	if (((EventArgs.Event == EInputEvent::IE_Pressed) || (EventArgs.Event == EInputEvent::IE_DoubleClick)) &&
		(EventArgs.Key == ClickKey))
	{
		FVector2D MousePosition;
		if (Project1GameViewportClient->GetMousePosition(MousePosition))
		{
			if (IsMouseCursorOverWidgetGeometry(MousePosition))
			{
				OnClicked.Broadcast(this);
			}
		}
	}
}

void UProject1ButtonBase::OnMouseCursorEntered()
{
	bCursorOver = true;
	MouseCursorEntered.Broadcast(this);
}

void UProject1ButtonBase::OnMouseCursorLeft()
{
	bCursorOver = false;
	MouseCursorLeft.Broadcast(this);
}
