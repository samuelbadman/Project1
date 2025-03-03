// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterControllerComponent.h"
#include "Pawns/Characters/Project1CharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Enums/CharacterGroundMovementState.h"

// Sets default values for this component's properties
UPlayerCharacterControllerComponent::UPlayerCharacterControllerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	RunInputMagnitude = 0.45f;
	Project1Character = nullptr;
}

void UPlayerCharacterControllerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	Project1Character->UpdateCapsuleRotation(DeltaTime);
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

	// Do not rotate character skeletal mesh with the character
	Project1Character->GetMesh()->SetAbsolute(false, true, false);
}

void UPlayerCharacterControllerComponent::OnMoveInput(const FVector& WorldDirection, float MoveInputMagnitude)
{
	Project1Character->SetTargetWorldOrientation(WorldDirection.ToOrientationQuat(), false);
	Project1Character->SetGroundMovementState((MoveInputMagnitude < RunInputMagnitude) ? ECharacterGroundMovementState::Walk : ECharacterGroundMovementState::Run);
	Project1Character->AddMovementInput(WorldDirection);
}
