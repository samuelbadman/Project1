// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/Project1ObjectBase.h"
#include "InteractionBase.generated.h"

// Interaction event delegates client game systems can bind to
DECLARE_MULTICAST_DELEGATE_OneParam(FOnInteractionStartedDelegate, UInteractionBase* /* Interaction */);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnInteractionCompletedDelegate, UInteractionBase* /* Interaction */);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnInteractionCanceledDelegate, UInteractionBase* /* Interaction */);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnInteractionCompletionPercentChangedDelegate, UInteractionBase* /* Interaction */);

struct FInteractionDescription
{
	float HoldDurationSeconds{ 0.1f };
};

/**
 * 
 */
UCLASS()
class UInteractionBase : public UProject1ObjectBase
{
	GENERATED_BODY()
	
private:
	static constexpr float MinPercentComplete{ 0.0f };
	static constexpr float MaxPercentComplete{ 1.0f };

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

	FORCEINLINE float GetCompletionPercent() const { return CompletionPercent; }

protected:
	// Sets the completion percent, clamping the new value in the range 0 - 1
	void SetCompletionPercent(float Percent);

	// Sets the completion percent to the minimum value
	void ClearCompletionPercent();

	// Helper function executing common functionality to complete the interaction
	void CompleteInteraction();
};
