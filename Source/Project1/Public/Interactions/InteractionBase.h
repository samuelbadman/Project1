// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/Project1ObjectBase.h"
#include "InteractionBase.generated.h"

// Interaction event delegates client game systems can bind to
DECLARE_MULTICAST_DELEGATE_OneParam(FOnInteractionStartedDelegate, UInteractionBase* /* Interaction */);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnInteractionCompletedDelegate, UInteractionBase* /* Interaction */);

/**
 * 
 */
UCLASS()
class UInteractionBase : public UProject1ObjectBase
{
	GENERATED_BODY()
	
private:
	static constexpr float PercentComplete{ 1.0f };

public:
	FOnInteractionStartedDelegate OnInteractionStartedDelegate{};
	FOnInteractionCompletedDelegate OnInteractionCompletedDelegate{};

private:
	// Completion percent in the range 0 - 1
	float CompletionPercent{ 0.0f };

public:
	// Debug
	virtual void BeginDestroy() override;

	virtual void OnInteractInputPressed() {};
	virtual void OnInteractInputHeld() {};
	virtual void OnInteractInputReleased() {};
	virtual bool IsComplete() const;

	FORCEINLINE float GetCompletionPercent() const { return CompletionPercent; }

protected:
	// Sets the completion percent, clamping the new value in the range 0 - 1
	void SetCompletionPercent(float Percent);

	// Helper function executing common functionality to complete the interaction
	void CompleteInteraction();
};
