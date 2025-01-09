// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Project1ActorComponentBase.h"
#include "PlayerCharacterControllerComponent.generated.h"

class UCharacterMovementComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT1_API UPlayerCharacterControllerComponent : public UProject1ActorComponentBase
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	float CapsuleRotationSpeed{ 7.5f };

	UPROPERTY(EditAnywhere)
	float MeshRotationSpeed{ 7.5f };

	UPROPERTY(EditAnywhere)
	float RunInputMagnitude{ 0.45f };

	UPROPERTY(EditAnywhere)
	float WalkSpeed{ 300.0f };

	UPROPERTY(EditAnywhere)
	float RunSpeed{ 600.0f };

	TObjectPtr<ACharacter> Character{ nullptr };
	TObjectPtr<UCharacterMovementComponent> CharacterMovementComponent{ nullptr };
	TObjectPtr<USkeletalMeshComponent> CharacterSkeletalMeshComponent{ nullptr };

	FQuat TargetCapsuleWorldOrientation{ FQuat::Identity };

public:	
	// Sets default values for this component's properties
	UPlayerCharacterControllerComponent();

	void SetupNewPossessedPawn(TObjectPtr<APawn> Pawn);
	void AddMovement(const FVector& WorldDirection, float MoveInputMagnitude);

	FORCEINLINE void SetTargetCapsuleWorldOrientation(const FQuat& TargetOrientation) { TargetCapsuleWorldOrientation = TargetOrientation; }

private:
	// Called every frame
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void UpdateGroundMovementState(float MoveInputMagnitude);
};
