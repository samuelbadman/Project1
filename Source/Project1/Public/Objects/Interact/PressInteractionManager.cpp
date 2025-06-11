// Fill out your copyright notice in the Description page of Project Settings.


#include "PressInteractionManager.h"
#include "Interfaces/Interactable.h"

void UPressInteractionManager::StartInteraction(const TObjectPtr<AActor> Interactable, const TObjectPtr<AActor> Interactor)
{
	// Starting a single press interaction. Interact with the interactable
	OnInteractionStartedDelegate.ExecuteIfBound();
	IInteractable::Execute_OnInteractedWith(Interactable, Interactor);
	OnInteractionCompleteDelegate.ExecuteIfBound();
}
