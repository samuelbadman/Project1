// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayerCameraManager.h"
#include "Actors/Cameras/PlayerCamera.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/StreamableManager.h"
#include "GameInstances/Project1GameInstanceBase.h"
#include "Kismet/GameplayStatics.h"

void AGamePlayerCameraManager::UpdateCamera(float DeltaTime)
{
	Super::UpdateCamera(DeltaTime);

}

void AGamePlayerCameraManager::BeginPlay()
{
	Super::BeginPlay();

	// Load player camera actor class and spawn player camera actor into the world
	if (UKismetSystemLibrary::IsValidSoftClassReference(PlayerCameraActorClass))
	{
		PlayerCameraActorClassStreamableHandle = CastChecked<UProject1GameInstanceBase>(UGameplayStatics::GetGameInstance(this))->GetStreamableManager().RequestAsyncLoad(
			PlayerCameraActorClass.ToSoftObjectPath(),
			FStreamableDelegate::CreateLambda([this]() {
				// Loaded player camera actor class. Spawn actor class into the world with the same transform as the player pawn
				FActorSpawnParameters SpawnInfo = {};
				SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
				PlayerCameraActor = GetWorld()->SpawnActor<APlayerCamera>(
					PlayerCameraActorClassStreamableHandle->GetLoadedAsset<UClass>(), 
					UGameplayStatics::GetPlayerPawn(this, 0)->GetActorTransform(), 
					SpawnInfo
				);
			}));
	}
}
