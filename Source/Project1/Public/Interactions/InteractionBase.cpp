// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionBase.h"

bool UInteractionBase::IsComplete() const
{
	return CompletionPercent >= MaxPercentComplete;
}

void UInteractionBase::SetCompletionPercent(float Percent)
{
	CompletionPercent = FMath::Clamp(Percent, MinPercentComplete, MaxPercentComplete);
	OnInteractionCompletionPercentChangedDelegate.Broadcast(this);
}

void UInteractionBase::ClearCompletionPercent()
{
	SetCompletionPercent(MinPercentComplete);
}

void UInteractionBase::CompleteInteraction()
{
	SetCompletionPercent(MaxPercentComplete);
	OnInteractionCompletedDelegate.Broadcast(this);
}
