// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponents/Project1ActorComponentBase.h"
#include "AICharacterControllerComponent.generated.h"

class UCharacterMovementComponent;

enum class EAICharacterGroundMovementStates : uint8
{
	Walk,
	Run
	// Sprint
};

/**
 *
 */
UCLASS()
class PROJECT1_API UAICharacterControllerComponent : public UProject1ActorComponentBase
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	float CapsuleRotationSpeed{ 7.5f };

	//UPROPERTY(EditAnywhere)
	//float MeshRotationSpeed{ 7.5f };

	// TODO: Move data into a component/data asset/character that can be defined per character as different characters may move at different speeds
	UPROPERTY(EditAnywhere)
	float WalkSpeed{ 300.0f };

	// TODO: Move data into a component/data asset/character that can be defined per character as different characters may move at different speeds
	UPROPERTY(EditAnywhere)
	float RunSpeed{ 600.0f };

	TObjectPtr<ACharacter> Character;
	TObjectPtr<UCharacterMovementComponent> CharacterMovementComponent;
	TObjectPtr<USkeletalMeshComponent> CharacterSkeletalMeshComponent;
	FQuat TargetCapsuleWorldOrientation;

public:
	UAICharacterControllerComponent();

	void SetupNewPawn(TObjectPtr<APawn> Pawn);
	void SetGroundMovementState(EAICharacterGroundMovementStates State);
	void SetTargetCapsuleWorldOrientation(const FQuat& TargetOrientation);

private:
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
