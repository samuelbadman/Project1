// Fill out your copyright notice in the Description page of Project Settings.


#include "Project1CharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/ActorComponents/Proj1CharacterMovementComponent.h"

// Sets default values
AProject1CharacterBase::AProject1CharacterBase(const FObjectInitializer& ObjectInitializer)
	: 
	Super(ObjectInitializer.SetDefaultSubobjectClass<UProj1CharacterMovementComponent>(ACharacter::CharacterMovementComponentName)),
	CharacterLinearWalkSpeed(141.0f),
	CharacterLinearRunSpeed(410.0f),
	World(nullptr),
	TargetCapsuleWorldOrientation(FQuat::Identity),
	DefaultMeshLocalRotation(FRotator::ZeroRotator)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
		RotateCharacter(TargetOrientation);
	}
}

void AProject1CharacterBase::SetMovementSpeed(float Speed)
{
	UCharacterMovementComponent* Movement{ GetCharacterMovement() };
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

	// Save local mesh rotation
	DefaultMeshLocalRotation = GetMesh()->GetRelativeRotation();

	// Set default target player character capsule rotation
	TargetCapsuleWorldOrientation = GetActorQuat();
}

void AProject1CharacterBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UpdateCapsuleRotation(DeltaSeconds);
}

bool AProject1CharacterBase::IsConsideredForViewLockOn_Implementation()
{
	return true;
}

void AProject1CharacterBase::UpdateCapsuleRotation(float DeltaTime)
{
	RotateCharacter(FMath::QInterpConstantTo(GetActorQuat(), TargetCapsuleWorldOrientation, DeltaTime, 10.0f));
}

void AProject1CharacterBase::RotateCharacter(const FQuat& Rotation)
{
	SetActorRotation(Rotation);
}
