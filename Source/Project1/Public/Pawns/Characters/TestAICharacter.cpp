// Fill out your copyright notice in the Description page of Project Settings.


#include "TestAICharacter.h"

ATestAICharacter::ATestAICharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	FootstepSound(nullptr),
	FootstepSoundAttenuation(nullptr),
	World(nullptr)
{
}

void ATestAICharacter::BeginPlay()
{
	Super::BeginPlay();

	World = GetWorld();
}

FVector ATestAICharacter::GetAIRequestedVelocity(const FVector& AIMoveVelocity)
{
	// This function implements AI character movement that is moved with MoveTo from the AI controller that supports turning with respect to the character's capsule rotation
	// rate defined in the character attributes data asset
	return (FMath::QInterpConstantTo(GetActorForwardVector().ToOrientationQuat(),
		AIMoveVelocity.ToOrientationQuat(),
		World->GetDeltaSeconds(),
		5.0f /*Capsule rotation rate*/).Vector() * AIMoveVelocity.Size());
}
