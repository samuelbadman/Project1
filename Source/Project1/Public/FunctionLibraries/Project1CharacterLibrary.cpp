// Fill out your copyright notice in the Description page of Project Settings.


#include "Project1CharacterLibrary.h"
#include "Kismet/GameplayStatics.h"

void UProject1CharacterLibrary::GatherFootstepData(FFootstepData& OutFootstepData, TObjectPtr<UWorld> World, TObjectPtr<USkeletalMeshComponent> CharacterMesh, 
	const FName& FootBoneName)
{
	static const float TraceDistance{ 100.0f };

	// Zero out output data
	OutFootstepData = {};

	// Find the hit where the foot impacts with the ground 
	const FVector TraceStart{ CharacterMesh->GetBoneLocation(FootBoneName, EBoneSpaces::WorldSpace) };
	const FVector TraceEnd{ TraceStart + (FVector::DownVector * TraceDistance) };

	FHitResult TraceHitResult;
	if (World->LineTraceSingleByChannel(TraceHitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility))
	{
		OutFootstepData.StepLocation = TraceHitResult.ImpactPoint;
	}
}

void UProject1CharacterLibrary::PlayFootstepFX(TObjectPtr<UWorld> WorldContextObject, TObjectPtr<USkeletalMeshComponent> CharacterMesh,
	const FName& FootBoneName, TObjectPtr<USoundBase> FootstepSound, TObjectPtr<USoundAttenuation> FootstepSoundAttenuation)
{
	// Get footstep data
	FFootstepData FootstepData;
	UProject1CharacterLibrary::GatherFootstepData(FootstepData, WorldContextObject, CharacterMesh, FootBoneName);

	PlayFootstepFX(FootstepData, WorldContextObject, FootstepSound, FootstepSoundAttenuation);
}

void UProject1CharacterLibrary::PlayFootstepFX(const FFootstepData& FootstepData, TObjectPtr<UWorld> WorldContextObject,
	TObjectPtr<USoundBase> FootstepSound, TObjectPtr<USoundAttenuation> FootstepSoundAttenuation)
{
	// Play footstep sound at step location if sound is valid
	if (IsValid(FootstepSound))
	{
		UGameplayStatics::PlaySoundAtLocation(WorldContextObject, FootstepSound, FootstepData.StepLocation, 1.0f, 1.0f, 0.0f, FootstepSoundAttenuation);
	}
}
