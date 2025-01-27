// Fill out your copyright notice in the Description page of Project Settings.


#include "Project1ButtonBase.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"
#include "GameViewportClients/Project1GameViewportClientBase.h"

void UProject1ButtonBase::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (const TObjectPtr<UImage> Image = GetImage())
	{
		Image->SetBrush(NormalBrush);
	}
}

void UProject1ButtonBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Project1GameViewportClient = CastChecked<UProject1GameViewportClientBase>(UGameplayStatics::GetGameInstance(this)->GetGameViewportClient());

	if (bStartActivated)
	{
		Activate();
	}
}

void UProject1ButtonBase::NativeDestruct()
{
	if (bActivated)
	{
		Project1GameViewportClient->MouseMoved.Remove(OnMouseMovedDelegateHandle);
		Project1GameViewportClient->OnInputKey.Remove(OnInputKeyDelegateHandle);
	}

	Super::NativeDestruct();
}

void UProject1ButtonBase::Activate()
{
	OnMouseMovedDelegateHandle = Project1GameViewportClient->MouseMoved.AddUObject(this, &UProject1ButtonBase::OnMouseMoved);
	OnInputKeyDelegateHandle = Project1GameViewportClient->OnInputKey.AddUObject(this, &UProject1ButtonBase::OnInputKey);
	bActivated = true;
}

void UProject1ButtonBase::Deactivate()
{
	Project1GameViewportClient->MouseMoved.Remove(OnMouseMovedDelegateHandle);
	OnMouseMovedDelegateHandle.Reset();

	Project1GameViewportClient->OnInputKey.Remove(OnInputKeyDelegateHandle);
	OnInputKeyDelegateHandle.Reset();

	if (const TObjectPtr<UImage> Image = GetImage())
	{
		Image->SetBrush(NormalBrush);
	}

	bActivated = false;
}

void UProject1ButtonBase::MakeHovered()
{
	if (bHovered)
	{
		return;
	}

	if (const TObjectPtr<UImage> Image = GetImage())
	{
		Image->SetBrush(HoveredBrush);

		bHovered = true;
		OnHovered.Broadcast(this);
	}
}

void UProject1ButtonBase::MakeUnhovered()
{
	if (!bHovered)
	{
		return;
	}

	if (const TObjectPtr<UImage> Image = GetImage())
	{
		Image->SetBrush(NormalBrush);

		bHovered = false;
		OnUnhovered.Broadcast(this);
	}
}

void UProject1ButtonBase::PressButton()
{
	OnPressed.Broadcast(this);
}

void UProject1ButtonBase::OnMouseMoved(const FVector2D& NewMousePosition, const FVector2D& OldMousePosition, const FVector2D& MouseMoveDelta)
{
	if (IsCursorInsideWidgetGeometry(NewMousePosition))
	{
		if (!bHovered)
		{
			MakeHovered();
		}
	}
	else
	{
		if (bHovered)
		{
			if (bCanMouseUnhoverButton)
			{
				MakeUnhovered();
			}
		}
	}
}

void UProject1ButtonBase::OnInputKey(const FInputKeyEventArgs& EventArgs)
{
	if (((EventArgs.Event == EInputEvent::IE_Pressed) || (EventArgs.Event == EInputEvent::IE_DoubleClick)) &&
		(EventArgs.Key == ClickKey))
	{
		FVector2D MousePosition;
		if (Project1GameViewportClient->GetMousePosition(MousePosition))
		{
			if (IsCursorInsideWidgetGeometry(MousePosition))
			{
				OnClicked.Broadcast(this);
			}
		}
	}
}
