// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Project1ActorBase.h"
#include "PlayerCamera.generated.h"

class USpringArmComponent;
class UCameraComponent;

/**
 * 
 */
UCLASS()
class APlayerCamera : public AProject1ActorBase
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> SceneComponent{ nullptr };

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> SpringArmComponent{ nullptr };

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> CameraComponent{ nullptr };

public:
	APlayerCamera();
};
