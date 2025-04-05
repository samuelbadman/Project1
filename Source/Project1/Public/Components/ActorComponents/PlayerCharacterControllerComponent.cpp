// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterControllerComponent.h"
#include "Pawns/Characters/Project1CharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values for this component's properties
UPlayerCharacterControllerComponent::UPlayerCharacterControllerComponent()
	: RunInputMagnitude(0.45f),
	bConstrainPlayerToWalk(false),
	Project1Character(nullptr)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

void UPlayerCharacterControllerComponent::SetConstrainPlayerToWalk(bool Constrain)
{
	bConstrainPlayerToWalk = Constrain;
}

void UPlayerCharacterControllerComponent::FlipConstrainPlayerToWalk()
{
	bConstrainPlayerToWalk = !bConstrainPlayerToWalk;
}

void UPlayerCharacterControllerComponent::OnPossessPawn(TObjectPtr<APawn> Pawn)
{
	// Get pawn as character
	Project1Character = CastChecked<AProject1CharacterBase>(Pawn);

	// Clear character use controller rotation settings
	Project1Character->bUseControllerRotationPitch = false;
	Project1Character->bUseControllerRotationYaw = false;
	Project1Character->bUseControllerRotationRoll = false;

	// Do not rotate character with movement
	Project1Character->GetCharacterMovement()->bOrientRotationToMovement = false;
}

void UPlayerCharacterControllerComponent::OnMoveInput(const FVector& WorldDirection, float MoveInputMagnitude)
{
	Project1Character->SetTargetWorldOrientation(WorldDirection.ToOrientationQuat(), false);
	Project1Character->SetMovementSpeed((MoveInputMagnitude < RunInputMagnitude) ? 410.0f : 410.0f);
	Project1Character->AddMovementInput(WorldDirection);
}
