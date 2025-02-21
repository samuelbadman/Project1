// Fill out your copyright notice in the Description page of Project Settings.


#include "Goal_Common_MoveToLocation.h"
#include "Components/ActorComponents/AICharacterControllerComponent.h"
#include "Pawns/Characters/Project1CharacterBase.h"

UGoal_Common_MoveToLocation::UGoal_Common_MoveToLocation()
{
	TargetLocation = FVector::ZeroVector;
	AcceptanceRadius = -1.0f;
	OwningAI = nullptr;
}

void UGoal_Common_MoveToLocation::Stop(TObjectPtr<AProject1AIControllerBase> AI)
{
	AI->StopMovement();
	RemoveMoveCompleteListener();
}

void UGoal_Common_MoveToLocation::Start(TObjectPtr<AProject1AIControllerBase> AI)
{
	OwningAI = AI;
	AI->GetAICharacterController()->SetGroundMovementState(GroundMovementState);
	AI->MoveToLocation(TargetLocation, AcceptanceRadius);
	AI->ReceiveMoveCompleted.AddDynamic(this, &UGoal_Common_MoveToLocation::OnMoveComplete);
}

void UGoal_Common_MoveToLocation::Tick(TObjectPtr<AProject1AIControllerBase> AI, float DeltaSeconds)
{
	// Set target capsule orientation
	FVector TargetMovementVector{ TargetLocation - (AI->GetPawn()->GetActorLocation()) };
	// Zero out Z movement component as characters move on the flat XY plane
	TargetMovementVector.Z = 0.0f;
	AI->GetAICharacterController()->SetCharacterWorldOrientation(TargetMovementVector.ToOrientationQuat(), false);
}

void UGoal_Common_MoveToLocation::Initialize(const FVector& InTargetLocation, ECharacterGroundMovementState InGroundMovementState, float InAcceptanceRadius)
{
	TargetLocation = InTargetLocation;
	GroundMovementState = InGroundMovementState;
	AcceptanceRadius = InAcceptanceRadius;
}

void UGoal_Common_MoveToLocation::OnMoveComplete(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
	RemoveMoveCompleteListener();
	OwningAI->RemoveSubGoal(this);
}

void UGoal_Common_MoveToLocation::RemoveMoveCompleteListener()
{
	OwningAI->ReceiveMoveCompleted.RemoveDynamic(this, &UGoal_Common_MoveToLocation::OnMoveComplete);
}
