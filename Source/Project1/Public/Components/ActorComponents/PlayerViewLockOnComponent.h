// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponents/Project1ActorComponentBase.h"
#include "PlayerViewLockOnComponent.generated.h"

class APlayerController;
class IViewLockOnTargetInterface;

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
	float ViewLockOnMaxDepth{ 2000.0f };

public:
	void OnLockOnInput(TObjectPtr<UWorld> World, TObjectPtr<APlayerController> PlayerController, const FVector& ViewWorldLocation);

private:
	void GetPotentialLockOnTargets(TObjectPtr<UWorld> World, TObjectPtr<APlayerController> PlayerController, const FVector& ViewWorldLocation, 
		TArray<IViewLockOnTargetInterface*>& OutPotentialTargets);
};
