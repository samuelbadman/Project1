// Fill out your copyright notice in the Description page of Project Settings.


#include "Goal_Common_MoveToLocation.h"
#include "Components/ActorComponents/AICharacterControllerComponent.h"

UGoal_Common_MoveToLocation::UGoal_Common_MoveToLocation()
	:
	TargetLocation(FVector::ZeroVector),
	AcceptanceRadius(-1.0f),
	CharacterMovementSpeed(410.0f),
	OwningAI(nullptr)
{
}

void UGoal_Common_MoveToLocation::Stop(TObjectPtr<AProject1AIControllerBase> AI)
{
	AI->StopMovement();
	RemoveMoveCompleteListener();
}

void UGoal_Common_MoveToLocation::Start(TObjectPtr<AProject1AIControllerBase> AI)
{
	OwningAI = AI;

	//AI->GetAICharacterController()->SetMovementSpeed(410.0f);
	AI->MoveToLocation(TargetLocation, AcceptanceRadius);
	AI->ReceiveMoveCompleted.AddDynamic(this, &UGoal_Common_MoveToLocation::OnMoveComplete);
}

void UGoal_Common_MoveToLocation::Tick(TObjectPtr<AProject1AIControllerBase> AI, float DeltaSeconds)
{
	AI->GetAICharacterController()->SetCharacterWorldOrientation(AI->GetPawn()->GetVelocity().ToOrientationQuat(), false);
}

void UGoal_Common_MoveToLocation::Initialize(const FVector& InTargetLocation, float InCharacterMovementSpeed, float InAcceptanceRadius)
{
	TargetLocation = InTargetLocation;
	CharacterMovementSpeed = InCharacterMovementSpeed;
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
