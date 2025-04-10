// Fill out your copyright notice in the Description page of Project Settings.


#include "Goal_Common_MoveToLocation.h"
#include "Actors/Pawns/Characters/Project1CharacterBase.h"

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

	CastChecked<AProject1CharacterBase>(AI->GetCharacter())->SetMovementSpeed(CharacterMovementSpeed);
	AI->MoveToLocation(TargetLocation, AcceptanceRadius);
	AI->ReceiveMoveCompleted.AddDynamic(this, &UGoal_Common_MoveToLocation::OnMoveComplete);
}

void UGoal_Common_MoveToLocation::Tick(TObjectPtr<AProject1AIControllerBase> AI, float DeltaSeconds)
{
	CastChecked<AProject1CharacterBase>(AI->GetCharacter())->SetTargetWorldOrientation(AI->GetPawn()->GetVelocity().ToOrientationQuat(), false);
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
