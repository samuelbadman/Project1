// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/Project1ObjectBase.h"
#include "HoldInteractManager.generated.h"

DECLARE_DELEGATE(FOnHoldInteractStarted);
DECLARE_DELEGATE_OneParam(FOnHoldInteractTickedDelegate, float /* PercentComplete */);
DECLARE_DELEGATE(FOnHoldInteractCanceled);
DECLARE_DELEGATE(FOnHoldInteractComplete);

struct FHoldInteractState
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
class UHoldInteractManager : public UProject1ObjectBase
{
	GENERATED_BODY()
	
public:
	FOnHoldInteractStarted OnHoldInteractStartedDelegate{};
	FOnHoldInteractTickedDelegate OnHoldInteractTickedDelegate{};
	FOnHoldInteractCanceled OnHoldInteractCanceledDelegate{};
	FOnHoldInteractComplete OnHoldInteractCompleteDelegate{};

private:
	TObjectPtr<UWorld> World{ nullptr };
	FHoldInteractState HoldInteractState{};

public:
	void Initialize();
	void StartHoldInteract(TObjectPtr<AActor> Interactor, TObjectPtr<AActor> Interactable);
	void TickHoldInteract(TObjectPtr<AActor> Interactor);
	void OnInteractInputCompleted(TObjectPtr<AActor> Interactor, TObjectPtr<AActor> Interactable);
	bool IsInHoldInteract() const;

private:
	void ResetHoldInteractState();
	void CompleteHoldInteractState(const TObjectPtr<AActor> Interactor);
	void CancelHoldInteractState(const TObjectPtr<AActor> Interactor);
};
