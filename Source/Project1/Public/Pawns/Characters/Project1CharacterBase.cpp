// Fill out your copyright notice in the Description page of Project Settings.


#include "Project1CharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AProject1CharacterBase::AProject1CharacterBase()
{
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

	// Automatically possess AI when the character is placed in the world or spawned
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}
