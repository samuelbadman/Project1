// Fill out your copyright notice in the Description page of Project Settings.


#include "Project1ButtonWidgetBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameViewportClients/Project1GameViewportClientBase.h"

#include "Kismet/KismetSystemLibrary.h"

void UProject1ButtonWidgetBase::MakeActive()
{
	NativeOnBecomeActive();
	OnBecomeActive();
	OnBecomeActiveDelegate.Broadcast();
}

void UProject1ButtonWidgetBase::EndActive()
{
	NativeOnEndActive();
	OnEndActive();
	OnEndActiveDelegate.Broadcast();
}

void UProject1ButtonWidgetBase::Press()
{
	NativeOnPressed();
	OnPressed();
	OnPressedDelegate.Broadcast();
}

void UProject1ButtonWidgetBase::BeginDestroy()
{
	Super::BeginDestroy();
	GameViewportClient->GetOnMouseMovedDelegate().Remove(OnMouseMovedDelegateHandle);
	OnMouseMovedDelegateHandle.Reset();
}

void UProject1ButtonWidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	GameViewportClient = CastChecked<UProject1GameViewportClientBase>(UGameplayStatics::GetGameInstance(this)->GetGameViewportClient());

	OnMouseMovedDelegateHandle = GameViewportClient->GetOnMouseMovedDelegate().AddWeakLambda(this,
		[this](const FVector2D& NewMousePosition, const FVector2D& OldMousePosition, const FVector2D& MouseMoveDelta) {
			const bool NewUnderMouse = IsWidgetGeometryUnderMouse(NewMousePosition);

			if (NewUnderMouse != bUnderMouse)
			{
				if (NewUnderMouse)
				{
					// Mouse cursor has entered button geometry
					NativeOnMouseEnteredGeometry();
					OnMouseEnteredGeometry();
					OnMouseEnteredGeometryDelegate.Broadcast(this);
				}
				else
				{
					// Mouse cursor has left button geometry
					NativeOnMouseLeftGeometry();
					OnMouseLeftGeometry();
					OnMouseLeftGeometryDelegate.Broadcast(this);
				}

				bUnderMouse = NewUnderMouse;
			}
		});
}
