// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacterControllerComponent.h"
#include "Pawns/Characters/Project1CharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"

UAICharacterControllerComponent::UAICharacterControllerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	Project1Character = nullptr;
}

void UAICharacterControllerComponent::OnPossessPawn(TObjectPtr<APawn> Pawn)
{
	// Get pawn as character
	Project1Character = CastChecked<AProject1CharacterBase>(Pawn);

	// Clear character use controller rotation settings
	Project1Character->bUseControllerRotationPitch = false;
	Project1Character->bUseControllerRotationYaw = false;
	Project1Character->bUseControllerRotationRoll = false;

	// Do not rotate character with movement
	Project1Character->GetCharacterMovement()->bOrientRotationToMovement = false;

	// Do not rotate character skeletal mesh with the character
	Project1Character->GetMesh()->SetAbsolute(false, true, false);
}

void UAICharacterControllerComponent::SetCharacterWorldOrientation(const FQuat& Orientation, bool Instant)
{
	Project1Character->SetTargetWorldOrientation(Orientation, Instant);
}
