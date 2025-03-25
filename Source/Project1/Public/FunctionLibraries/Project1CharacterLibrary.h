// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Project1CharacterLibrary.generated.h"

class UCommonFootstepFXDataAsset;

struct FFootstepData
{
	FVector StepLocation{ FVector::ZeroVector };
};

/**
 * 
 */
UCLASS()
class PROJECT1_API UProject1CharacterLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static void GatherFootstepData(FFootstepData& OutFootstepData, TObjectPtr<UWorld> World, TObjectPtr<USkeletalMeshComponent> CharacterMesh, const FName& FootBoneName);
	static void PlayFootstepFX(TObjectPtr<UWorld> WorldContextObject, TObjectPtr<USkeletalMeshComponent> CharacterMesh, const FName& FootBoneName, 
		TObjectPtr<USoundBase> FootstepSound, TObjectPtr<USoundAttenuation> FootstepSoundAttenuation);
	static void PlayFootstepFX(const FFootstepData& FootstepData, TObjectPtr<UWorld> WorldContextObject, TObjectPtr<USoundBase> FootstepSound,
		TObjectPtr<USoundAttenuation> FootstepSoundAttenuation);
};
