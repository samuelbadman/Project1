// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawns/Characters/Project1CharacterBase.h"
#include "AIDevCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT1_API AAIDevCharacter : public AProject1CharacterBase
{
	GENERATED_BODY()
	
private:
	TObjectPtr<UWorld> World;

public:
	AAIDevCharacter(const FObjectInitializer& ObjectInitializer);

private:
	void BeginPlay() override;
	FVector GetAIRequestedVelocity(const FVector& AIMoveVelocity) override;
};
