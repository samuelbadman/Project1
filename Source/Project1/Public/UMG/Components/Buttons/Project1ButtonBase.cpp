// Fill out your copyright notice in the Description page of Project Settings.


#include "Project1ButtonBase.h"
#include "Components/Border.h"
#include "Components/BorderSlot.h"
#include "Kismet/GameplayStatics.h"
#include "Controllers/PlayerControllers/Project1PlayerControllerBase.h"
#include "GameViewportClients/Project1GameViewportClientBase.h"

void UProject1ButtonBase::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (const TObjectPtr<UBorder> Border = GetBorder())
	{
		Border->SetBrush((IsHovered()) ? HoveredBrush : NormalBrush);

		const TArray<UPanelSlot*>& BorderSlots{ Border->GetSlots() };
		if (!BorderSlots.IsEmpty())
		{
			CastChecked<UBorderSlot>(Border->GetSlots()[0])->SetPadding(ContentPadding);
		}

		if (bLastMouseInputsActivated)
		{
			ActivateMouseInput();
		}
	}
}

void UProject1ButtonBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Project1PlayerController = CastChecked<AProject1PlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));
	Project1GameViewportClient = CastChecked<UProject1GameViewportClientBase>(UGameplayStatics::GetGameInstance(this)->GetGameViewportClient());
}

void UProject1ButtonBase::NativeDestruct()
{
	bLastMouseInputsActivated = bMouseInputsActivated;

	if (bMouseInputsActivated)
	{
		DeactivateMouseInput();
	}

	Super::NativeDestruct();
}

void UProject1ButtonBase::ActivateMouseInput()
{
	if (bMouseInputsActivated)
	{
		return;
	}

	OnMouseCursorVisibilityChangedDelegateHandle = Project1PlayerController->MouseCursorVisibilityChanged.AddUObject(this, &UProject1ButtonBase::OnMouseCursorVisibilityChanged);
	OnMouseMovedDelegateHandle = Project1GameViewportClient->MouseMoved.AddUObject(this, &UProject1ButtonBase::OnMouseMoved);

	if (bEnableMouseClickEvents)
	{
		OnInputKeyDelegateHandle = Project1GameViewportClient->OnInputKey.AddUObject(this, &UProject1ButtonBase::OnInputKey);
	}

	bMouseInputsActivated = true;
}

void UProject1ButtonBase::DeactivateMouseInput()
{
	if (!bMouseInputsActivated)
	{
		return;
	}

	Project1PlayerController->MouseCursorVisibilityChanged.Remove(OnMouseCursorVisibilityChangedDelegateHandle);
	OnMouseCursorVisibilityChangedDelegateHandle.Reset();

	Project1GameViewportClient->MouseMoved.Remove(OnMouseMovedDelegateHandle);
	OnMouseMovedDelegateHandle.Reset();

	// bEnableMouseClickEvents is only changed in the editor and remains constant during game runtime. Input key delegate is only assigned when bEnableMouseClickEvents is true
	if (bEnableMouseClickEvents)
	{
		Project1GameViewportClient->OnInputKey.Remove(OnInputKeyDelegateHandle);
		OnInputKeyDelegateHandle.Reset();
	}

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
		OnMouseCursorOverWidget();
	}
	else if ((NewVisibility == EMouseCursorVisibility::Hidden) &&
		(bNewCursorOver))
	{
		OnMouseCursorLeftWidget();
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
			OnMouseCursorOverWidget();
		}
	}
	else
	{
		if (bCursorOver)
		{
			OnMouseCursorLeftWidget();
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

	// Generate click event, otherwise 
	// Is the input the click key
	if (EventArgs.Key == ClickKey)
	{
		// Was the click key pressed or double clicked
		if (((EventArgs.Event == EInputEvent::IE_Pressed) || (EventArgs.Event == EInputEvent::IE_DoubleClick)))
		{
			// If the mouse cursor is over the button widget geometry
			FVector2D MousePosition;
			if (Project1GameViewportClient->GetMousePosition(MousePosition))
			{
				if (IsMouseCursorOverWidgetGeometry(MousePosition))
				{
					// Generate click event
					bClickInputHeld = true;
					OnClicked.Broadcast(this);
				}
			}
		}
		// Else, was the click key released
		else if (EventArgs.Event == EInputEvent::IE_Released)
		{
			// If the click input is being held down
			if (bClickInputHeld)
			{
				// Generate released event
				bClickInputHeld = false;
				OnReleased.Broadcast(this);
			}
		}
	}
}

void UProject1ButtonBase::OnMouseCursorOverWidget()
{
	bCursorOver = true;
	OnMouseCursorOver.Broadcast(this);

	if (bGenerateHoverEvents)
	{
		MakeHovered();
	}
}

void UProject1ButtonBase::OnMouseCursorLeftWidget()
{
	bCursorOver = false;
	OnMouseCursorLeft.Broadcast(this);

	if (bGenerateHoverEvents)
	{
		MakeUnhovered();
	}
}
