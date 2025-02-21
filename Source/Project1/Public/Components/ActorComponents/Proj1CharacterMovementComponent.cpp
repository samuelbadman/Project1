// Fill out your copyright notice in the Description page of Project Settings.


#include "Proj1CharacterMovementComponent.h"
#include "Pawns/Characters/Project1CharacterBase.h"

UProj1CharacterMovementComponent::UProj1CharacterMovementComponent()
{
	World = nullptr;
	Project1Character = nullptr;
}

void UProj1CharacterMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	World = GetWorld();
	// Get owner project 1 character
	Project1Character = CastChecked<AProject1CharacterBase>(GetOwner());
}

void UProj1CharacterMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	if (MoveVelocity.SizeSquared() < UE_KINDA_SMALL_NUMBER)
	{
		return;
	}

	if (ShouldPerformAirControlForPathFollowing())
	{
		const FVector FallVelocity = MoveVelocity.GetClampedToMaxSize(GetMaxSpeed());
		PerformAirControlForPathFollowing(FallVelocity, GetGravitySpaceZ(FallVelocity));
		return;
	}

	RequestedVelocity = Project1Character->GetAIRequestedVelocity(MoveVelocity);
	bHasRequestedVelocity = true;
	bRequestedMoveWithMaxSpeed = bForceMaxSpeed;

	if (IsMovingOnGround())
	{
		RequestedVelocity = ProjectToGravityFloor(RequestedVelocity);
	}

	Project1Character->UpdateCapsuleRotation(World->GetDeltaSeconds());
}
