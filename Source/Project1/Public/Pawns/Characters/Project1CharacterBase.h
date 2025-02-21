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

	TObjectPtr<UWorld> World;
	FQuat TargetCapsuleWorldOrientation;
	ECharacterGroundMovementState CurrentGroundMovementState;

public:
	// Sets default values for this character's properties
	AProject1CharacterBase(const FObjectInitializer& ObjectInitializer);

	// Provides the opportunity for characters to provide a different velocity when the AI navigation system requests a velocity. This can be used to implement a turning radius for AI
	// characters when changing directions
	virtual FVector GetAIRequestedVelocity(const FVector& AIMoveVelocity);

	// Sets the capsule and mesh component world orientations over time. The character's capsule and mesh component will be rotated towards this orientation each update at the rates
	// defined in character attributes data asset. If Instant is true the capsule will be rotated on the same frame this function is called instead of over time
	void SetWorldOrientation(const FQuat& TargetOrientation, bool Instant);
	void UpdateCapsuleRotation(float DeltaTime);
	void SetGroundMovementState(ECharacterGroundMovementState State);

	FORCEINLINE TObjectPtr<UCharacterAttributesDataAsset> GetCharacterAttributes() const { return CharacterAttributes; }

protected:
	void BeginPlay() override;

private:
	void SetCharacterRotation(const FQuat& Rotation);
};
