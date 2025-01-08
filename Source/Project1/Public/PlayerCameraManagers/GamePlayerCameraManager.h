// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCameraManagers/Project1PlayerCameraManagerBase.h"
#include "GamePlayerCameraManager.generated.h"

class APlayerCamera;
struct FStreamableHandle;

/**
 * 
 */
UCLASS()
class PROJECT1_API AGamePlayerCameraManager : public AProject1PlayerCameraManagerBase
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly)
	TSoftClassPtr<APlayerCamera> PlayerCameraActorClass{ nullptr };

	TObjectPtr<APlayerCamera> PlayerCameraActor{ nullptr };
	TSharedPtr<FStreamableHandle> PlayerCameraActorClassStreamableHandle{ nullptr };

private:
	/**
	 * Performs per-tick camera update. Called once per tick after all other actors have been ticked.
	 */
	void UpdateCamera(float DeltaTime) override;

	void BeginPlay() override;
};
