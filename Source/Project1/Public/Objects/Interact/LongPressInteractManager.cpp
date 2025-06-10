// Fill out your copyright notice in the Description page of Project Settings.


#include "LongPressInteractManager.h"
#include "Interfaces/Interactable.h"

void ULongPressInteractManager::Initialize()
{
	// Get the object's owning world
	World = GetWorld();
}

void ULongPressInteractManager::StartLongPressInteract(TObjectPtr<AActor> Interactor, TObjectPtr<AActor> Interactable)
{
	// Setup long press interact state for this interaction
	LongPressInteractState.Interactable = Interactable;
	LongPressInteractState.TotalDuration = IInteractable::Execute_GetLongPressInteractDuration(Interactable);

	// Start the long press interact
	IInteractable::Execute_OnLongPressInteractStarted(Interactable, Interactor);
}

void ULongPressInteractManager::TickLongPressInteract(TObjectPtr<AActor> Interactor)
{
	// Get time delta since last tick
	const float DeltaTime{ World->GetDeltaSeconds() };

	// Progress current long press interact state
	LongPressInteractState.ElapsedDuration += DeltaTime;

	// TODO: Update player feedback systems with new long press interact progress

	// Notify object being interacted with it has ticked
	const float PercentComplete{ LongPressInteractState.CalculatePercentComplete() };
	IInteractable::Execute_OnLongPressInteractTicked(LongPressInteractState.Interactable, Interactor, DeltaTime, PercentComplete);
	OnLongPressInteractTickedDelegate.ExecuteIfBound(PercentComplete);

	// Check if the long press interact has completed
	if (LongPressInteractState.IsComplete())
	{
		// Complete the long press interact. Reset the long press interact state is done inside CompleteLongPressInteractState
		CompleteLongPressInteractState(Interactor);
	}
}

void ULongPressInteractManager::OnInteractInputCompleted(TObjectPtr<AActor> Interactor, TObjectPtr<AActor> Interactable)
{
	// Is the long press interact complete? 
	if (LongPressInteractState.IsComplete())
	{
		// Complete the long press interact. Reset the long press interact state is done inside CompleteLongPressInteractState
		CompleteLongPressInteractState(Interactor);
	}
	else
	{
		// Cancel the long press interact
		IInteractable::Execute_OnLongPressInteractCanceled(LongPressInteractState.Interactable, Interactor, LongPressInteractState.CalculatePercentComplete());

		// Reset the long press interact state
		ResetLongPressInteractState();
	}
}

bool ULongPressInteractManager::IsInLongPressInteract() const
{
	return (LongPressInteractState.Interactable != nullptr);
}

void ULongPressInteractManager::ResetLongPressInteractState()
{
	LongPressInteractState = {};
}

void ULongPressInteractManager::CompleteLongPressInteractState(const TObjectPtr<AActor> Interactor)
{
	// Copy interactable pointer as it is needed to call interactable interface OnInteractedWith after the long press interact state structure has been reset, losing the original 
	// interactable pointer
	const TObjectPtr<AActor> Interactable{ LongPressInteractState.Interactable };

	// Complete the interaction and reset the interact state
	IInteractable::Execute_OnLongPressInteractCompleted(LongPressInteractState.Interactable, Interactor);
	ResetLongPressInteractState();

	// Notify the interactable it has been interacted with
	IInteractable::Execute_OnInteractedWith(Interactable, Interactor);
}
