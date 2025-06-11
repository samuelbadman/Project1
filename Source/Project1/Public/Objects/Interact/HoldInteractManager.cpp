// Fill out your copyright notice in the Description page of Project Settings.


#include "HoldInteractManager.h"
#include "Interfaces/Interactable.h"
#include "Structures/InteractableDescription.h"

void UHoldInteractManager::Initialize()
{
	// Get the object's owning world
	World = GetWorld();
}

void UHoldInteractManager::StartHoldInteract(TObjectPtr<AActor> Interactor, TObjectPtr<AActor> Interactable)
{
	// Setup hold interact state for this interaction
	FInteractableDescription InteractableDesc;
	IInteractable::Execute_GetInteractableDescription(Interactable, InteractableDesc);

	HoldInteractState.Interactable = Interactable;
	HoldInteractState.TotalDuration = InteractableDesc.HoldInteractDuration;

	// Start the hold interact
	IInteractable::Execute_OnHoldInteractStarted(Interactable, Interactor);
	OnHoldInteractStartedDelegate.ExecuteIfBound();
}

void UHoldInteractManager::TickHoldInteract(TObjectPtr<AActor> Interactor)
{
	// Get time delta since last tick
	const float DeltaTime{ World->GetDeltaSeconds() };

	// Progress current hold interact state
	HoldInteractState.ElapsedDuration += DeltaTime;

	// Notify object being interacted with it has ticked
	const float PercentComplete{ HoldInteractState.CalculatePercentComplete() };
	IInteractable::Execute_OnHoldInteractTicked(HoldInteractState.Interactable, Interactor, DeltaTime, PercentComplete);
	OnHoldInteractTickedDelegate.ExecuteIfBound(PercentComplete);

	// Check if the hold interact has completed
	if (HoldInteractState.IsComplete())
	{
		// Complete the hold interact. Reset the hold interact state is done inside CompleteHoldInteractState
		CompleteHoldInteractState(Interactor);
	}
}

void UHoldInteractManager::OnInteractInputCompleted(TObjectPtr<AActor> Interactor, TObjectPtr<AActor> Interactable)
{
	// Is the hold interact complete? 
	if (HoldInteractState.IsComplete())
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

bool UHoldInteractManager::IsInHoldInteract() const
{
	return (HoldInteractState.Interactable != nullptr);
}

void UHoldInteractManager::ResetHoldInteractState()
{
	HoldInteractState = {};
}

void UHoldInteractManager::CompleteHoldInteractState(const TObjectPtr<AActor> Interactor)
{
	// Copy interactable pointer as it is needed to call interactable interface OnInteractedWith after the hold interact state structure has been reset, losing the original 
	// interactable pointer
	const TObjectPtr<AActor> Interactable{ HoldInteractState.Interactable };

	// Complete the interaction and reset the interact state
	IInteractable::Execute_OnHoldInteractCompleted(HoldInteractState.Interactable, Interactor);
	OnHoldInteractCompleteDelegate.ExecuteIfBound();

	// Reset the hold interact state
	ResetHoldInteractState();

	// Notify the interactable it has been interacted with
	IInteractable::Execute_OnInteractedWith(Interactable, Interactor);
}

void UHoldInteractManager::CancelHoldInteractState(const TObjectPtr<AActor> Interactor)
{
	IInteractable::Execute_OnHoldInteractCanceled(HoldInteractState.Interactable, Interactor, HoldInteractState.CalculatePercentComplete());
	OnHoldInteractCanceledDelegate.ExecuteIfBound();

	// Reset the hold interact state
	ResetHoldInteractState();
}
