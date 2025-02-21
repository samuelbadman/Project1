// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Proj1CharacterMovementComponent.generated.h"

class AProject1CharacterBase;

/**
 * 
 */
UCLASS()
class PROJECT1_API UProj1CharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
	
private:
	TObjectPtr<AProject1CharacterBase> Project1Character;

public:
	UProj1CharacterMovementComponent();

private:
	void BeginPlay() override;
	void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
};
