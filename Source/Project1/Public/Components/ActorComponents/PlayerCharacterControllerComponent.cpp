// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterControllerComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values for this component's properties
UPlayerCharacterControllerComponent::UPlayerCharacterControllerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}

// Called every frame
void UPlayerCharacterControllerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
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

void UPlayerCharacterControllerComponent::UpdateGroundMovementState(float MoveInputMagnitude)
{
	if (MoveInputMagnitude < RunInputMagnitude)
	{
		// Walking
		CharacterMovementComponent->MinAnalogWalkSpeed = WalkSpeed;
		CharacterMovementComponent->MaxWalkSpeed = WalkSpeed;
	}
	else
	{
		// Running
		CharacterMovementComponent->MinAnalogWalkSpeed = RunSpeed;
		CharacterMovementComponent->MaxWalkSpeed = RunSpeed;
	}
}

void UPlayerCharacterControllerComponent::SetupNewPawn(TObjectPtr<APawn> Pawn)
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

void UPlayerCharacterControllerComponent::AddMovement(const FVector& WorldDirection, float MoveInputMagnitude)
{
	TargetCapsuleWorldOrientation = WorldDirection.ToOrientationQuat();

	UpdateGroundMovementState(MoveInputMagnitude);

	Character->AddMovementInput(WorldDirection);
}
