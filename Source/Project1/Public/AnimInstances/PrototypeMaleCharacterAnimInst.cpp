// Fill out your copyright notice in the Description page of Project Settings.


#include "PrototypeMaleCharacterAnimInst.h"
#include "DataAssets/CharacterAttributesDataAsset.h"
#include "Enums/CharacterGroundMovementState.h"

UPrototypeMaleCharacterAnimInst::UPrototypeMaleCharacterAnimInst()
	: 
	bIsWalking(false),
	bIsRunning(false),
	OwnerVelocity(FVector::ZeroVector),
	OwnerGroundMovementState(ECharacterGroundMovementState::Max)
{
}

void UPrototypeMaleCharacterAnimInst::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (IsValid(GetProject1CharacterOwner()))
	{
		OwnerVelocity = GetProject1CharacterOwner()->GetVelocity();
		OwnerGroundMovementState = GetProject1CharacterOwner()->GetCurrentGroundMovementState();
	}
}

void UPrototypeMaleCharacterAnimInst::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	// Determine ground movement state of character
	const bool bIsIdle{ FVector2D(OwnerVelocity.X, OwnerVelocity.Y).SizeSquared() == 0.0f };
	if (!bIsIdle)
	{
		bIsWalking = (OwnerGroundMovementState == ECharacterGroundMovementState::Walk);
		bIsRunning = (OwnerGroundMovementState == ECharacterGroundMovementState::Run);
	}
	else
	{
		bIsWalking = bIsRunning = false;
	}
}
