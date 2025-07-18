// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/AI/Goals/AIGoalBase.h"
#include "Goal_Common_MoveToLocation.generated.h"


/**
 * 
 */
UCLASS()
class PROJECT1_API UGoal_Common_MoveToLocation : public UAIGoalBase
{
	GENERATED_BODY()
	
private:
	FVector TargetLocation;
	float AcceptanceRadius;
	float CharacterMovementSpeed;
	TObjectPtr<AProject1AIControllerBase> OwningAI;

public:
	UGoal_Common_MoveToLocation();

	void Initialize(const FVector& InTargetLocation, float InCharacterMovementSpeed, float InAcceptanceRadius = -1.0f);

private:
	void Stop(TObjectPtr<AProject1AIControllerBase> AI) override;
	void Start(TObjectPtr<AProject1AIControllerBase> AI) override;
	void Tick(TObjectPtr<AProject1AIControllerBase> AI, float DeltaSeconds) override;

	UFUNCTION()
	void OnMoveComplete(FAIRequestID RequestID, EPathFollowingResult::Type Result);

	void RemoveMoveCompleteListener();
};
