// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractionManagerBase.h"
#include "HoldInteractionManager.generated.h"

struct FHoldInteractionState
{
	TObjectPtr<AActor> Interactable{ nullptr };
	float TotalDuration{ 0.0f };
	float ElapsedDuration{ 0.0f };

	bool IsComplete() const
	{
		return ElapsedDuration >= TotalDuration;
	}

	float CalculatePercentComplete() const
	{
		return ((ElapsedDuration / TotalDuration) * 100.0f);
	}
};

/**
 * 
 */
UCLASS()
class UHoldInteractionManager : public UInteractionManagerBase
{
	GENERATED_BODY()
	
private:
	FHoldInteractionState HoldInteractionState{};

public:
	virtual void StartInteraction(const TObjectPtr<AActor> Interactable, const TObjectPtr<AActor> Interactor) override;
	virtual void TickInteraction(const TObjectPtr<AActor> Interactable, const TObjectPtr<AActor> Interactor) override;

	void OnInteractInputCompleted(TObjectPtr<AActor> Interactor, TObjectPtr<AActor> Interactable);
	bool IsInHoldInteract() const;

private:
	void ResetHoldInteractState();
	void CompleteHoldInteractState(const TObjectPtr<AActor> Interactor);
	void CancelHoldInteractState(const TObjectPtr<AActor> Interactor);
};
