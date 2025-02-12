// Fill out your copyright notice in the Description page of Project Settings.


#include "Project1CharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DataAssets/CharacterAttributesDataAsset.h"

// Sets default values
AProject1CharacterBase::AProject1CharacterBase()
{
	// Set class default values
	CharacterAttributes = nullptr;
	TargetCapsuleWorldOrientation = FQuat::Identity;
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	// Set colliding character components to overlap camera collision channel
	static constexpr ECollisionChannel CameraCollisionChannel{ ECC_Camera };
	static constexpr ECollisionResponse CameraCollisionChannelCharacterResponse{ ECR_Overlap };
	GetCapsuleComponent()->SetCollisionResponseToChannel(CameraCollisionChannel, CameraCollisionChannelCharacterResponse);
	GetMesh()->SetCollisionResponseToChannel(CameraCollisionChannel, CameraCollisionChannelCharacterResponse);
	// Clear inherit controller rotation settings
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	// Do not orient character to movement. This will be done by the controller
	GetCharacterMovement()->bOrientRotationToMovement = false;
	// Automatically possess character with AI controller whether spawned or placed in world unless a player controller possesses the character
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AProject1CharacterBase::SetTargetCapsuleWorldOrientation(const FQuat& TargetOrientation)
{
	TargetCapsuleWorldOrientation = TargetOrientation;
}

void AProject1CharacterBase::BeginPlay()
{
	Super::BeginPlay();
	// Set default target player character capsule rotation
	TargetCapsuleWorldOrientation = GetActorQuat();
}

void AProject1CharacterBase::UpdateCapsuleRotation(float DeltaTime)
{
	// Update character capsule rotation
	const FQuat NewCharacterOrientation{ FMath::QInterpConstantTo(GetActorQuat(), TargetCapsuleWorldOrientation, DeltaTime, CharacterAttributes->CapsuleRotationSpeed) };
	SetActorRotation(NewCharacterOrientation);
	// Update player character skeletal mesh rotation. Keep the mesh aligned with the capsule
	const FRotator TargetCharacterMeshRotation{ TargetCapsuleWorldOrientation };
	// TODO: This sometimes rotates the mesh in the opposite direction to the capsule. Will this be a problem? Matching mesh rotation to capsule for now
	//GetMesh()->SetWorldRotation(FMath::QInterpConstantTo(GetMesh()->GetComponentQuat(), TargetCharacterMeshRotation.Quaternion(),
	//	DeltaTime, CharacterAttributes->MeshRotationSpeed));
	GetMesh()->SetWorldRotation(NewCharacterOrientation);
}
