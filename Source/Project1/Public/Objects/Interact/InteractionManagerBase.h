// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/Project1ObjectBase.h"
#include "InteractionManagerBase.generated.h"

// These are only single delegates as for now it is only intended for the interact prompt screen to bind to interaction manager events
DECLARE_DELEGATE(FOnInteractionStarted);
DECLARE_DELEGATE_OneParam(FOnInteractionTickedDelegate, float /* PercentComplete */);
DECLARE_DELEGATE(FOnInteractionCanceled);
DECLARE_DELEGATE(FOnInteractionComplete);

/**
 * 
 */
UCLASS()
class UInteractionManagerBase : public UProject1ObjectBase
{
	GENERATED_BODY()
	
public:
	FOnInteractionStarted OnInteractionStartedDelegate{};
	FOnInteractionTickedDelegate OnInteractionTickedDelegate{};
	FOnInteractionCanceled OnInteractionCanceledDelegate{};
	FOnInteractionComplete OnInteractionCompleteDelegate{};

private:
	TObjectPtr<UWorld> World{ nullptr };

public:
	virtual void Initialize();
	virtual void StartInteraction(const TObjectPtr<AActor> Interactable, const TObjectPtr<AActor> Interactor);
	virtual void TickInteraction(const TObjectPtr<AActor> Interactable, const TObjectPtr<AActor> Interactor);

protected:
	TObjectPtr<UWorld> GetCachedWorld() const { return World; }
};
