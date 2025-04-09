// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/ViewLockOnTargetInterface.h"
#include "Project1CharacterBase.generated.h"

UCLASS()
class PROJECT1_API AProject1CharacterBase : public ACharacter, public IViewLockOnTargetInterface
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	float CharacterLinearWalkSpeed;

	UPROPERTY(EditAnywhere)
	float CharacterLinearRunSpeed;

	UPROPERTY(EditAnywhere)
	float CapsuleRotationRate;

	TObjectPtr<UWorld> World;
	FQuat TargetCapsuleWorldOrientation;
	FRotator DefaultMeshLocalRotation;

public:
	// Sets default values for this character's properties
	AProject1CharacterBase(const FObjectInitializer& ObjectInitializer);

	// Provides the opportunity for characters to provide a different velocity when the AI navigation system requests a velocity. Passed AI move velocity is in the direction
	// AI systems want the character to move regardless of the character's current velocity. This is used to implement a turning radius for AI characters when changing directions
	virtual FVector GetAIRequestedVelocity(const FVector& AIMoveVelocity);

	// Sets the target capsule and mesh component world orientations. The character's capsule and mesh component will be rotated towards this orientation each update at the rate
	// defined in character attributes data asset. If Instant is true the capsule will be rotated on the same frame this function is called instead of over time
	void SetTargetWorldOrientation(const FQuat& TargetOrientation, bool Instant);
	void SetMovementSpeed(float Speed);

	FORCEINLINE float GetLinearWalkSpeed() const { return CharacterLinearWalkSpeed; }
	FORCEINLINE float GetLinearRunSpeed() const { return CharacterLinearRunSpeed; }

protected:
	void BeginPlay() override;
	void Tick(float DeltaSeconds) override;
	bool IsConsideredForViewLockOn_Implementation() override;

private:
	void UpdateCapsuleRotation(float DeltaTime);
	void RotateCharacter(const FQuat& Rotation);
};
