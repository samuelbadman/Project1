// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponents/Project1ActorComponentBase.h"
#include "AICharacterControllerComponent.generated.h"

class AProject1CharacterBase;
enum class ECharacterGroundMovementState : uint8;

/**
 *
 */
UCLASS()
class PROJECT1_API UAICharacterControllerComponent : public UProject1ActorComponentBase
{
	GENERATED_BODY()

private:
	TObjectPtr<AProject1CharacterBase> Project1Character;

public:
	UAICharacterControllerComponent();

	void OnPossessPawn(TObjectPtr<APawn> Pawn);

	void SetCharacterWorldOrientation(const FQuat& Orientation, bool Instant);
};
