// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Project1CharacterBase.generated.h"

class UCharacterAttributesDataAsset;

UCLASS()
class PROJECT1_API AProject1CharacterBase : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UCharacterAttributesDataAsset> CharacterAttributes;

public:
	// Sets default values for this character's properties
	AProject1CharacterBase();

	FORCEINLINE TObjectPtr<UCharacterAttributesDataAsset> GetCharacterAttributes() const { return CharacterAttributes; }
};
