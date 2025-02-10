// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AIControllers/Project1AIControllerBase.h"
#include "AIGoalBase.generated.h"

/**
 * 
 */
UCLASS(NotBlueprintable, BlueprintType, EditInlineNew, DefaultToInstanced)
class PROJECT1_API UAIGoalBase : public UObject
{
	GENERATED_BODY()

public:
	virtual void Stop(TObjectPtr<AProject1AIControllerBase> AI);
	virtual void Start(TObjectPtr<AProject1AIControllerBase> AI);
	virtual void Tick(TObjectPtr<AProject1AIControllerBase> AI, float DeltaSeconds);
	virtual void ReevaluateSubGoal(TObjectPtr<AProject1AIControllerBase> AI);
};
