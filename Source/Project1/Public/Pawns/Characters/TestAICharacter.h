// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawns/Characters/Project1CharacterBase.h"
#include "TestAICharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT1_API ATestAICharacter : public AProject1CharacterBase
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, Category = "Footsteps")
	TObjectPtr<USoundBase> FootstepSound;
	UPROPERTY(EditAnywhere, Category = "Footsteps")
	TObjectPtr<USoundAttenuation> FootstepSoundAttenuation;

	TObjectPtr<UWorld> World;

public:
	ATestAICharacter(const FObjectInitializer& ObjectInitializer);

private:
	void BeginPlay() override;
	FVector GetAIRequestedVelocity(const FVector& AIMoveVelocity) override;
	void OnFootstepNotify(const FName& FootBoneName) override;
};
