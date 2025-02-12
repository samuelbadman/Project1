// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Project1ActorComponentBase.h"
#include "PlayerCharacterControllerComponent.generated.h"

class AProject1CharacterBase;
class UCharacterMovementComponent;
class UCharacterAttributesDataAsset;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT1_API UPlayerCharacterControllerComponent : public UProject1ActorComponentBase
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Move")
	float RunInputMagnitude;

	TObjectPtr<AProject1CharacterBase> Project1Character;
	TObjectPtr<UCharacterMovementComponent> CharacterMovementComponent;
	TObjectPtr<USkeletalMeshComponent> CharacterSkeletalMeshComponent;
	TObjectPtr<UCharacterAttributesDataAsset> CharacterAttributes;

public:	
	// Sets default values for this component's properties
	UPlayerCharacterControllerComponent();

	void SetupNewPawn(TObjectPtr<APawn> Pawn);
	void AddMovement(const FVector& WorldDirection, float MoveInputMagnitude);

private:
	// Called every frame
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void UpdateGroundMovementState(float MoveInputMagnitude);
};
