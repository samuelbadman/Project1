// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionBase.h"

bool UInteractionBase::IsComplete() const
{
	return CompletionPercent >= MaxCompletionPercent;
}

void UInteractionBase::SetCompletionPercent(float Percent)
{
	CompletionPercent = FMath::Clamp(Percent, MinCompletionPercent, MaxCompletionPercent);
	OnInteractionCompletionPercentChangedDelegate.Broadcast(this);
}

void UInteractionBase::ClearCompletionPercent()
{
	SetCompletionPercent(MinCompletionPercent);
}

void UInteractionBase::CompleteInteraction()
{
	SetCompletionPercent(MaxCompletionPercent);
	OnInteractionCompletedDelegate.Broadcast(this);
}
