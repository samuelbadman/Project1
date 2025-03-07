// Fill out your copyright notice in the Description page of Project Settings.


#include "Project1CharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DataAssets/CharacterAttributesDataAsset.h"
#include "Enums/CharacterGroundMovementState.h"
#include "Components/ActorComponents/Proj1CharacterMovementComponent.h"

// Sets default values
AProject1CharacterBase::AProject1CharacterBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UProj1CharacterMovementComponent>(ACharacter::CharacterMovementComponentName)),
	MeshRotationOffset(FRotator::ZeroRotator)
{
	// Set class default values
	CharacterAttributes = nullptr;
	World = nullptr;
	TargetCapsuleWorldOrientation = FQuat::Identity;
	CurrentGroundMovementState = ECharacterGroundMovementState::Max;
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

void AProject1CharacterBase::SetTargetWorldOrientation(const FQuat& TargetOrientation, bool Instant)
{
	TargetCapsuleWorldOrientation = TargetOrientation;
	if (Instant)
	{
		SetCharacterRotation(TargetOrientation, TargetOrientation);
	}
}

void AProject1CharacterBase::SetGroundMovementState(ECharacterGroundMovementState State)
{
	if (CurrentGroundMovementState == State)
	{
		return;
	}

	const TObjectPtr<UCharacterMovementComponent> Movement{ GetCharacterMovement() };
	float Speed{ 0.0f };
	switch (State)
	{
	case ECharacterGroundMovementState::Walk: Speed = CharacterAttributes->WalkSpeed; break;
	case ECharacterGroundMovementState::Run: Speed = CharacterAttributes->RunSpeed;	break;
	}

	Movement->MinAnalogWalkSpeed = Speed;
	Movement->MaxWalkSpeed = Speed;
}

FVector AProject1CharacterBase::GetAIRequestedVelocity(const FVector& AIMoveVelocity)
{
	return AIMoveVelocity;
}

void AProject1CharacterBase::BeginPlay()
{
	Super::BeginPlay();
	World = GetWorld();
	// Set default target player character capsule rotation
	TargetCapsuleWorldOrientation = GetActorQuat();
}

void AProject1CharacterBase::SetCharacterRotation(const FQuat& Rotation, const FQuat& MeshRotation)
{
	SetActorRotation(Rotation);
	GetMesh()->SetWorldRotation(MeshRotation);
}

void AProject1CharacterBase::UpdateCapsuleRotation(float DeltaTime)
{
	const FQuat NewRotation{ FMath::QInterpConstantTo(GetActorQuat(), TargetCapsuleWorldOrientation, DeltaTime, CharacterAttributes->CapsuleRotationSpeed) };

	FRotator MeshRotation(NewRotation);
	MeshRotation += MeshRotationOffset;
	const FQuat NewMeshRotation{ FMath::QInterpConstantTo(GetMesh()->GetComponentQuat(), FQuat(MeshRotation), DeltaTime, CharacterAttributes->MeshRotationSpeed) };

	SetCharacterRotation(NewRotation, NewMeshRotation);
}
