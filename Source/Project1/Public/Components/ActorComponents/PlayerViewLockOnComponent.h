// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponents/Project1ActorComponentBase.h"
#include "PlayerViewLockOnComponent.generated.h"

class APlayerController;
class IViewLockOnTargetInterface;
class AGamePlayerCameraManager;

/**
 * 
 */
UCLASS()
class PROJECT1_API UPlayerViewLockOnComponent : public UProject1ActorComponentBase
{
	GENERATED_BODY()
	
private:
	// Objects in with a screen space depth larger than this number will not be considered to be locked on to with the view
	UPROPERTY(EditAnywhere)
	float ViewLockMaxDepth;

	TObjectPtr<UWorld> World;
	TObjectPtr<AGamePlayerCameraManager> GamePlayerCameraManager;
	FTimerHandle OverMaxDepthCheckTimerHandle;
	float OverMaxDepthCheckIntervalSeconds;

public:
	UPlayerViewLockOnComponent();

	void OnLockOnInput(TObjectPtr<APlayerController> PlayerController, const FVector& ViewWorldLocation);
	void SetGamePlayerCameraManager(TObjectPtr<AGamePlayerCameraManager> InGamePlayerCameraManager);

private:
	void GetPotentialLockOnTargets(TObjectPtr<APlayerController> PlayerController, const FVector& ViewWorldLocation, TArray<IViewLockOnTargetInterface*>& OutPotentialTargets);
	void CheckOverMaxDepth();
	void UnlockView();
};
