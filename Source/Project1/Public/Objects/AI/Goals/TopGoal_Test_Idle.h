// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/AI/Goals/AIGoalBase.h"
#include "TopGoal_Test_Idle.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT1_API UTopGoal_Test_Idle : public UAIGoalBase
{
	GENERATED_BODY()
	
private:
	void Start(TObjectPtr<AProject1AIControllerBase> AI) override;
	void ReevaluateSubGoal(TObjectPtr<AProject1AIControllerBase> AI) override;
};
