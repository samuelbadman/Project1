// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponents/Project1ActorComponentBase.h"
#include "Enums/AICharacterGroundMovementState.h"
#include "AICharacterControllerComponent.generated.h"

class AProject1CharacterBase;
class UCharacterMovementComponent;
class UCharacterAttributesDataAsset;

/**
 *
 */
UCLASS()
class PROJECT1_API UAICharacterControllerComponent : public UProject1ActorComponentBase
{
	GENERATED_BODY()

private:
	TObjectPtr<AProject1CharacterBase> Project1Character;
	TObjectPtr<UCharacterMovementComponent> CharacterMovementComponent;
	TObjectPtr<USkeletalMeshComponent> CharacterSkeletalMeshComponent;
	TObjectPtr<UCharacterAttributesDataAsset> CharacterAttributes;
	FQuat TargetCapsuleWorldOrientation;

public:
	UAICharacterControllerComponent();

	void SetupNewPawn(TObjectPtr<APawn> Pawn);
	void SetGroundMovementState(EAICharacterGroundMovementState State);
	void SetTargetCapsuleWorldOrientation(const FQuat& TargetOrientation);

private:
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
