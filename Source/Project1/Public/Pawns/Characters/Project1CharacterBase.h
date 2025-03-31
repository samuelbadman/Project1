// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/ViewLockOnTargetInterface.h"
#include "Project1CharacterBase.generated.h"

class UCharacterAttributesDataAsset;
enum class ECharacterGroundMovementState : uint8;

UCLASS()
class PROJECT1_API AProject1CharacterBase : public ACharacter, public IViewLockOnTargetInterface
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UCharacterAttributesDataAsset> CharacterAttributes;

	TObjectPtr<UWorld> World;
	FQuat TargetCapsuleWorldOrientation;
	ECharacterGroundMovementState CurrentGroundMovementState;
	FRotator DefaultMeshLocalRotation;

public:
	// Sets default values for this character's properties
	AProject1CharacterBase(const FObjectInitializer& ObjectInitializer);

	// Provides the opportunity for characters to provide a different velocity when the AI navigation system requests a velocity. This can be used to implement a turning radius for AI
	// characters when changing directions
	virtual FVector GetAIRequestedVelocity(const FVector& AIMoveVelocity);

	// Sets the target capsule and mesh component world orientations. The character's capsule and mesh component will be rotated towards this orientation each update at the rate
	// defined in character attributes data asset. If Instant is true the capsule will be rotated on the same frame this function is called instead of over time
	void SetTargetWorldOrientation(const FQuat& TargetOrientation, bool Instant);
	void UpdateCapsuleRotation(float DeltaTime);
	void SetGroundMovementState(ECharacterGroundMovementState State);

	virtual void OnFootstepNotify(const FName& FootBoneName);

	FORCEINLINE TObjectPtr<UCharacterAttributesDataAsset> GetCharacterAttributes() const { return CharacterAttributes; }
	FORCEINLINE ECharacterGroundMovementState GetCurrentGroundMovementState() const { return CurrentGroundMovementState; }

protected:
	void BeginPlay() override;
	bool IsConsideredForViewLockOn_Implementation() override;

private:
	void SetCharacterRotation(const FQuat& Rotation, const FQuat& MeshRotation);
};
