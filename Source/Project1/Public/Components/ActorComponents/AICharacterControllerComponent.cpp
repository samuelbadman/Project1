// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacterControllerComponent.h"
#include "Pawns/Characters/Project1CharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DataAssets/CharacterAttributesDataAsset.h"

UAICharacterControllerComponent::UAICharacterControllerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	Project1Character = nullptr;
	CharacterMovementComponent = nullptr;
	CharacterSkeletalMeshComponent = nullptr;
	CharacterAttributes = nullptr;
}

void UAICharacterControllerComponent::SetupNewPawn(TObjectPtr<APawn> Pawn)
{
	// Get pawn as character
	Project1Character = CastChecked<AProject1CharacterBase>(Pawn);

	// Get character movement component
	CharacterMovementComponent = Project1Character->GetCharacterMovement();

	// Get character skeletal mesh component
	CharacterSkeletalMeshComponent = Project1Character->GetMesh();

	// Get character attributes
	CharacterAttributes = Project1Character->GetCharacterAttributes();

	// Clear character use controller rotation settings
		Project1Character->bUseControllerRotationPitch = false;
	Project1Character->bUseControllerRotationYaw = false;
	Project1Character->bUseControllerRotationRoll = false;

	// Do not rotate character with movement
	CharacterMovementComponent->bOrientRotationToMovement = false;

	// Do not rotate character skeletal mesh with the character
	CharacterSkeletalMeshComponent->SetAbsolute(false, true, false);
}

void UAICharacterControllerComponent::SetGroundMovementState(EAICharacterGroundMovementState State)
{
	switch (State)
	{
	case EAICharacterGroundMovementState::Walk:
	{
		const float WalkSpeed{ CharacterAttributes->WalkSpeed };
		CharacterMovementComponent->MinAnalogWalkSpeed = WalkSpeed;
		CharacterMovementComponent->MaxWalkSpeed = WalkSpeed;
		break;
	}

	case EAICharacterGroundMovementState::Run:
	{
		const float RunSpeed{ CharacterAttributes->RunSpeed };
		CharacterMovementComponent->MinAnalogWalkSpeed = RunSpeed;
		CharacterMovementComponent->MaxWalkSpeed = RunSpeed;
		break;
	}
	}
}

void UAICharacterControllerComponent::SetControlledCharacterTargetCapsuleWorldOrientation(const FQuat& TargetOrientation)
{
	Project1Character->SetTargetCapsuleWorldOrientation(TargetOrientation);
}

void UAICharacterControllerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// Update character capsule rotation
	Project1Character->UpdateCapsuleRotation(DeltaTime);
}
