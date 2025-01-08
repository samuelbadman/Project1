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
UCLASS(meta = (PrioritizeCategories = "PlayerCameraSettings"))
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

	UPROPERTY(EditAnywhere, Category = "PlayerCameraSettings")
	float RotateInterpSpeed{ 2.0f };

	UPROPERTY(EditAnywhere, Category = "PlayerCameraSettings")
	float SpringArmLengthLookingUp{ 50.0f };

	UPROPERTY(EditAnywhere, Category = "PlayerCameraSettings")
	float SpringArmLengthLookingDown{ 400.0f };

	float CachedSpringArmTargetArmLength{ 0.0f };

public:
	APlayerCamera();

	void Rotate(float Pitch, float Yaw);

	FORCEINLINE float GetRotateInterpSpeed() const { return RotateInterpSpeed; }

private:
	void BeginPlay() override;
};
