// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionBase.h"

void UInteractionBase::BeginDestroy()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Cyan, FString::Printf(TEXT("Destroying interaction: %s"), *GetName()));

	Super::BeginDestroy();
}

bool UInteractionBase::IsComplete() const
{
	return CompletionPercent >= PercentComplete;
}

void UInteractionBase::SetCompletionPercent(float Percent)
{
	CompletionPercent = FMath::Clamp(Percent, 0.0f, 1.0f);
}

void UInteractionBase::CompleteInteraction()
{
	SetCompletionPercent(1.0f);
	OnInteractionCompletedDelegate.Broadcast(this);
}
