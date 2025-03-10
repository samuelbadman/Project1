// Fill out your copyright notice in the Description page of Project Settings.


#include "MannySimpleAnimInstance.h"
#include "Pawns/Characters/Project1CharacterBase.h"

UMannySimpleAnimInstance::UMannySimpleAnimInstance()
	: bIsMoving(false),
	ProjectCharacterOwner(nullptr),
	CharacterOwnerVelocity(FVector::ZeroVector)
{
}

void UMannySimpleAnimInstance::NativeInitializeAnimation()
{
	if (ProjectCharacterOwner = Cast<AProject1CharacterBase>(TryGetPawnOwner()))
	{
	}
}

void UMannySimpleAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (IsValid(ProjectCharacterOwner))
	{
		CharacterOwnerVelocity = ProjectCharacterOwner->GetVelocity();
	}
}

void UMannySimpleAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	bIsMoving = (CharacterOwnerVelocity.SquaredLength() > 0.0f);
}
