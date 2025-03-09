// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/AI/Goals/AIGoalBase.h"
#include "Goal_Test_Idle.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT1_API UGoal_Test_Idle : public UAIGoalBase
{
	GENERATED_BODY()
	
private:
	bool bJustMoved;

public:
	UGoal_Test_Idle();

private:
	void Start(TObjectPtr<AProject1AIControllerBase> AI) override;
	void ReevaluateSubGoal(TObjectPtr<AProject1AIControllerBase> AI) override;

	void AddMoveToRandomReachablePointSubGoal(TObjectPtr<AProject1AIControllerBase> AI);
};
