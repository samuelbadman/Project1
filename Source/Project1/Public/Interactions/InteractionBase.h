// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/Project1ObjectBase.h"
#include "Structures/InteractionDescription.h"
#include "Enumerations/InteractionType.h"
#include "InteractionBase.generated.h"

// Interaction event delegates client game systems can bind to
DECLARE_MULTICAST_DELEGATE_OneParam(FOnInteractionStartedDelegate, UInteractionBase* /* Interaction */);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnInteractionCompletedDelegate, UInteractionBase* /* Interaction */);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnInteractionCanceledDelegate, UInteractionBase* /* Interaction */);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnInteractionCompletionPercentChangedDelegate, UInteractionBase* /* Interaction */);

/**
 * 
 */
UCLASS()
class UInteractionBase : public UProject1ObjectBase
{
	GENERATED_BODY()
	
protected:
	static constexpr float MinCompletionPercent{ 0.0f };
	static constexpr float MaxCompletionPercent{ 1.0f };

public:
	FOnInteractionStartedDelegate OnInteractionStartedDelegate{};
	FOnInteractionCompletedDelegate OnInteractionCompletedDelegate{};
	FOnInteractionCanceledDelegate OnInteractionCanceledDelegate{};
	FOnInteractionCompletionPercentChangedDelegate OnInteractionCompletionPercentChangedDelegate{};

private:
	// Completion percent in the range 0 - 1
	float CompletionPercent{ 0.0f };

public:
	virtual void Initialize(const FInteractionDescription& Desc) {};
	virtual void OnInteractInputPressed() {};
	virtual void OnInteractInputHeld(float DeltaTime) {};
	virtual void OnInteractInputReleased() {};
	virtual void Tick(float DeltaTime) {};
	virtual bool IsComplete() const;
	virtual EInteractionType GetType() const { return EInteractionType::Undefined_Max; }

	// Returns the completion precent in the range 0 - 1
	FORCEINLINE float GetCompletionPercent() const { return CompletionPercent; }

protected:
	// Sets the completion percent, clamping the new value in the range 0 - 1. Does not check to see if the interaction is complete. This still needs to be done by client code
	void SetCompletionPercent(float Percent);

	// Sets the completion percent to the minimum value
	void ClearCompletionPercent();

	// Helper function executing common functionality to complete the interaction
	void CompleteInteraction();
};
