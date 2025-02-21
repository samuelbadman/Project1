// Fill out your copyright notice in the Description page of Project Settings.


#include "Proj1CharacterMovementComponent.h"
#include "Pawns/Characters/Project1CharacterBase.h"

UProj1CharacterMovementComponent::UProj1CharacterMovementComponent()
{
	Project1Character = nullptr;
}

void UProj1CharacterMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	// Get owner project 1 character
	Project1Character = CastChecked<AProject1CharacterBase>(GetOwner());
}

void UProj1CharacterMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	Project1Character->Move(MoveVelocity.GetSafeNormal());
}
