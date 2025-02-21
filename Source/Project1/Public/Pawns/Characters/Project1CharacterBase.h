// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Project1CharacterBase.generated.h"

class UCharacterAttributesDataAsset;
enum class ECharacterGroundMovementState : uint8;

UCLASS()
class PROJECT1_API AProject1CharacterBase : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UCharacterAttributesDataAsset> CharacterAttributes;

	UPROPERTY(EditAnywhere)
	bool bOnlyUpdateCapsuleRotationDuringMove;

	TObjectPtr<UWorld> World;
	FQuat TargetCapsuleWorldOrientation;
	ECharacterGroundMovementState CurrentGroundMovementState;

public:
	// Sets default values for this character's properties
	AProject1CharacterBase(const FObjectInitializer& ObjectInitializer);

	// Function called by player input and AI navigation to move the character. Allows sub character classes to implement custom movement logic by overriding this function
	virtual void Move(const FVector& DesiredDirection);

	void SetTargetCapsuleWorldOrientation(const FQuat& TargetOrientation);
	void SetOnlyUpdateCapsuleRotationDuringMove(bool NewValue);
	void SetGroundMovementState(ECharacterGroundMovementState State);

private:
	void BeginPlay() override;
	void Tick(float DeltaSeconds) override;

	void UpdateCapsuleRotation(float DeltaTime);
};
