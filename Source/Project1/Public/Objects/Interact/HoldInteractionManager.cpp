// Fill out your copyright notice in the Description page of Project Settings.


#include "HoldInteractionManager.h"
#include "Interfaces/Interactable.h"
#include "Structures/InteractableDescription.h"

void UHoldInteractionManager::StartInteraction(const TObjectPtr<AActor> Interactable, const TObjectPtr<AActor> Interactor)
{
	// Setup hold interact state for this interaction
	FInteractableDescription InteractableDesc;
	IInteractable::Execute_GetInteractableDescription(Interactable, InteractableDesc);

	HoldInteractionState.Interactable = Interactable;
	HoldInteractionState.TotalDuration = InteractableDesc.HoldInteractDuration;

	// Start the hold interact
	IInteractable::Execute_OnHoldInteractStarted(Interactable, Interactor);
	OnInteractionStartedDelegate.ExecuteIfBound();
}

void UHoldInteractionManager::TickInteraction(const TObjectPtr<AActor> Interactable, const TObjectPtr<AActor> Interactor)
{
	// Get time delta since last tick
	const float DeltaTime{ GetCachedWorld()->GetDeltaSeconds()};

	// Progress current hold interact state
	HoldInteractionState.ElapsedDuration += DeltaTime;

	// Notify object being interacted with it has ticked
	const float PercentComplete{ HoldInteractionState.CalculatePercentComplete() };
	IInteractable::Execute_OnHoldInteractTicked(HoldInteractionState.Interactable, Interactor, DeltaTime, PercentComplete);
	OnInteractionTickedDelegate.ExecuteIfBound(PercentComplete);

	// Check if the hold interact has completed
	if (HoldInteractionState.IsComplete())
	{
		// Complete the hold interact. Reset the hold interact state is done inside CompleteHoldInteractState
		CompleteHoldInteractState(Interactor);
	}
}

void UHoldInteractionManager::OnInteractInputCompleted(TObjectPtr<AActor> Interactor, TObjectPtr<AActor> Interactable)
{
	// Is the hold interact complete? 
	if (HoldInteractionState.IsComplete())
	{
		// Complete the hold interact
		CompleteHoldInteractState(Interactor);
	}
	else
	{
		// Cancel the hold interact
		CancelHoldInteractState(Interactor);
	}
}

bool UHoldInteractionManager::IsInHoldInteract() const
{
	return (HoldInteractionState.Interactable != nullptr);
}

void UHoldInteractionManager::ResetHoldInteractState()
{
	HoldInteractionState = {};
}

void UHoldInteractionManager::CompleteHoldInteractState(const TObjectPtr<AActor> Interactor)
{
	// Copy interactable pointer as it is needed to call interactable interface OnInteractedWith after the hold interact state structure has been reset, losing the original 
	// interactable pointer
	const TObjectPtr<AActor> Interactable{ HoldInteractionState.Interactable };

	// Complete the interaction and reset the interact state
	IInteractable::Execute_OnHoldInteractCompleted(HoldInteractionState.Interactable, Interactor);
	OnInteractionCompleteDelegate.ExecuteIfBound();

	// Reset the hold interact state
	ResetHoldInteractState();

	// Notify the interactable it has been interacted with
	IInteractable::Execute_OnInteractedWith(Interactable, Interactor);
}

void UHoldInteractionManager::CancelHoldInteractState(const TObjectPtr<AActor> Interactor)
{
	IInteractable::Execute_OnHoldInteractCanceled(HoldInteractionState.Interactable, Interactor, HoldInteractionState.CalculatePercentComplete());
	OnInteractionCanceledDelegate.ExecuteIfBound();

	// Reset the hold interact state
	ResetHoldInteractState();
}
