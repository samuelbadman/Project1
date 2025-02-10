// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/AI/Goals/AIGoalBase.h"
#include "Goal_Common_Wait.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT1_API UGoal_Common_Wait : public UAIGoalBase
{
	GENERATED_BODY()
	
private:
	float Duration;
	TObjectPtr<AProject1AIControllerBase> OwnerAI;
	FTimerManager* WorldTimerManager;
	FTimerHandle WaitTimerHandle;

public:
	UGoal_Common_Wait();

	void Initialize(float InDuration);

private:
	void Stop(TObjectPtr<AProject1AIControllerBase> AI) override;
	void Start(TObjectPtr<AProject1AIControllerBase> AI) override;

	void OnDurationElapsed();
};
