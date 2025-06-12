// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactions/InteractionBase.h"
#include "HoldInteraction.generated.h"

/**
 * 
 */
UCLASS()
class UHoldInteraction : public UInteractionBase
{
	GENERATED_BODY()
	
private:
	float HoldDurationSeconds{ 0.1f };
	float ElapsedSeconds{ 0.0f };

public:
	// Sets the total seconds the interact input needs to be held for
	void SetHoldDurationSeconds(float Seconds) { HoldDurationSeconds = Seconds; }

private:
	virtual void Initialize(const FInteractionDescription& Desc) override;
	virtual void OnInteractInputPressed() override;
	virtual void OnInteractInputHeld(float DeltaTime) override;
	virtual void OnInteractInputReleased() override;
};
