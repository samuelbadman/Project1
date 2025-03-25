// Fill out your copyright notice in the Description page of Project Settings.


#include "PrototypeMaleCharacterAnimInst.h"

UPrototypeMaleCharacterAnimInst::UPrototypeMaleCharacterAnimInst()
	: bIsWalking(false),
	PawnOwner(nullptr),
	PawnOwnerVelocity(FVector::ZeroVector)
{
}

void UPrototypeMaleCharacterAnimInst::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	PawnOwner = TryGetPawnOwner();
}

void UPrototypeMaleCharacterAnimInst::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (IsValid(PawnOwner))
	{
		PawnOwnerVelocity = PawnOwner->GetVelocity();
	}
}

void UPrototypeMaleCharacterAnimInst::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	bIsWalking = (PawnOwnerVelocity.SizeSquared() > 0.0f);
}
