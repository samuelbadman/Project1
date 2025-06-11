// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionManagerBase.h"

void UInteractionManagerBase::Initialize()
{
	// Get the world
	World = GetWorld();
}

void UInteractionManagerBase::StartInteraction(const TObjectPtr<AActor> Interactable, const TObjectPtr<AActor> Interactor)
{
	OnInteractionStartedDelegate.ExecuteIfBound();
}

void UInteractionManagerBase::TickInteraction(const TObjectPtr<AActor> Interactable, const TObjectPtr<AActor> Interactor)
{
	OnInteractionTickedDelegate.ExecuteIfBound(World->GetDeltaSeconds());
}
