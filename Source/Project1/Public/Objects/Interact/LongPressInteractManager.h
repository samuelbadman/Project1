// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/Project1ObjectBase.h"
#include "LongPressInteractManager.generated.h"

DECLARE_DELEGATE_OneParam(FOnLongPressInteractTickedDelegate, float /* PercentComplete */);

struct FLongPressInteractState
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
class ULongPressInteractManager : public UProject1ObjectBase
{
	GENERATED_BODY()
	
public:
	FOnLongPressInteractTickedDelegate OnLongPressInteractTickedDelegate{};

private:
	TObjectPtr<UWorld> World{ nullptr };
	FLongPressInteractState LongPressInteractState{};

public:
	void Initialize();
	void StartLongPressInteract(TObjectPtr<AActor> Interactor, TObjectPtr<AActor> Interactable);
	void TickLongPressInteract(TObjectPtr<AActor> Interactor);
	void OnInteractInputCompleted(TObjectPtr<AActor> Interactor, TObjectPtr<AActor> Interactable);
	bool IsInLongPressInteract() const;

private:
	void ResetLongPressInteractState();
	void CompleteLongPressInteractState(const TObjectPtr<AActor> Interactor);
};
