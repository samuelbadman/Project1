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
	void Move(const FVector& DesiredDirection) override;
};
