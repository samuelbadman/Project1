// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterAttributesDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT1_API UCharacterAttributesDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	float CapsuleRotationSpeed{ 7.5f };

	UPROPERTY(EditAnywhere)
	float WalkSpeed{ 300.0f };

	UPROPERTY(EditAnywhere)
	float RunSpeed{ 600.0f };
};
