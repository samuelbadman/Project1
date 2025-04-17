// Fill out your copyright notice in the Description page of Project Settings.


#include "PrototypeMaleCharacterAnimInst.h"

UPrototypeMaleCharacterAnimInst::UPrototypeMaleCharacterAnimInst()
	: bIsMoving(false),
	PawnOwner(nullptr)
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
		bIsMoving = (StaticCast<float>(PawnOwner->GetVelocity().Size()) > 3.0f);
	}
}
