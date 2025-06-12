// Fill out your copyright notice in the Description page of Project Settings.


#include "HoldInteraction.h"

void UHoldInteraction::Initialize(const FInteractionDescription& Desc)
{
	HoldDurationSeconds = Desc.HoldDurationSeconds;
}

void UHoldInteraction::OnInteractInputPressed()
{
	OnInteractionStartedDelegate.Broadcast(this);
}

void UHoldInteraction::OnInteractInputHeld(float DeltaTime)
{
	ElapsedSeconds += DeltaTime;
	SetCompletionPercent(ElapsedSeconds / HoldDurationSeconds);

	if (IsComplete())
	{
		CompleteInteraction();
	}
}

void UHoldInteraction::OnInteractInputReleased()
{
	if (!IsComplete())
	{
		OnInteractionCanceledDelegate.Broadcast(this);
		ClearCompletionPercent();
	}
}
