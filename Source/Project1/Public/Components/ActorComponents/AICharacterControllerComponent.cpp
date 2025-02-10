// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacterControllerComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UAICharacterControllerComponent::UAICharacterControllerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	Character = nullptr;
	CharacterMovementComponent = nullptr;
	CharacterSkeletalMeshComponent = nullptr;
	TargetCapsuleWorldOrientation = FQuat::Identity;
}

void UAICharacterControllerComponent::SetupNewPawn(TObjectPtr<APawn> Pawn)
{
	// Get pawn as character
	Character = CastChecked<ACharacter>(Pawn);

	// Get character movement component
	CharacterMovementComponent = Character->GetCharacterMovement();

	// Get character skeletal mesh component
	CharacterSkeletalMeshComponent = Character->GetMesh();

	// Clear character use controller rotation settings
	Character->bUseControllerRotationPitch = false;
	Character->bUseControllerRotationYaw = false;
	Character->bUseControllerRotationRoll = false;

	// Do not rotate character with movement
	CharacterMovementComponent->bOrientRotationToMovement = false;

	// Do not rotate character skeletal mesh with the character
	CharacterSkeletalMeshComponent->SetAbsolute(false, true, false);

	// Set default target player character capsule rotation
	TargetCapsuleWorldOrientation = Character->GetActorQuat();
}

void UAICharacterControllerComponent::SetGroundMovementState(EAICharacterGroundMovementStates State)
{
	switch (State)
	{
	case EAICharacterGroundMovementStates::Walk:
		CharacterMovementComponent->MinAnalogWalkSpeed = WalkSpeed;
		CharacterMovementComponent->MaxWalkSpeed = WalkSpeed;
		break;

	case EAICharacterGroundMovementStates::Run:
		CharacterMovementComponent->MinAnalogWalkSpeed = RunSpeed;
		CharacterMovementComponent->MaxWalkSpeed = RunSpeed;
		break;
	}
}

void UAICharacterControllerComponent::SetTargetCapsuleWorldOrientation(const FQuat& TargetOrientation)
{
	TargetCapsuleWorldOrientation = TargetOrientation;
}

void UAICharacterControllerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// Update character capsule rotation
	const FQuat NewCharacterOrientation{ FMath::QInterpConstantTo(Character->GetActorQuat(), TargetCapsuleWorldOrientation, DeltaTime, CapsuleRotationSpeed) };
	Character->SetActorRotation(NewCharacterOrientation);

	// Update player character skeletal mesh rotation. Keep the mesh aligned with the capsule
	FRotator TargetCharacterMeshRotation{ TargetCapsuleWorldOrientation };
	// TODO: This sometimes rotates the mesh in the opposite direction to the capsule. Will this be a problem? Matching mesh rotation to capsule for now
	//CharacterSkeletalMeshComponent->SetWorldRotation(FMath::QInterpConstantTo(CharacterSkeletalMeshComponent->GetComponentQuat(), TargetCharacterMeshRotation.Quaternion(),
	//	DeltaTime, MeshRotationSpeed));
	CharacterSkeletalMeshComponent->SetWorldRotation(NewCharacterOrientation);
}
