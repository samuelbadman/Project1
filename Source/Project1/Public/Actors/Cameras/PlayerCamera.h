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
	TObjectPtr<USceneComponent> CameraParentComponent{ nullptr };

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> CameraComponent{ nullptr };

	UPROPERTY(EditAnywhere, Category = "PlayerCameraSettings")
	float RotateInterpSpeed{ 2.0f };

	UPROPERTY(EditAnywhere, Category = "PlayerCameraSettings")
	float LocationInterpSpeed{ 3.0f };

	// The distance the camera component is offset from the actor along the relative X axis when the view look direction is parallel with the ground
	UPROPERTY(EditAnywhere, Category = "PlayerCameraSettings", meta = (DisplayName = "Relative X Offset"))
	float RelativeXOffset{ -300.0f };

	// The distance the camera component is offset from the actor along the relative X axis when the view is looking up
	UPROPERTY(EditAnywhere, Category = "PlayerCameraSettings", meta = (DisplayName = "Relative X Offset Looking Up"))
	float RelativeXOffsetLookingUp{ -50.0f };

	// The distance the camera component is offset from the actor along the relative X axis when the view looking down
	UPROPERTY(EditAnywhere, Category = "PlayerCameraSettings", meta = (DisplayName = "Relative X Offset Looking Down"))
	float RelativeXOffsetLookingDown{ -400.0f };

public:
	APlayerCamera();

	void Rotate(float Pitch, float Yaw);

	FORCEINLINE float GetRotateInterpSpeed() const { return RotateInterpSpeed; }
	FORCEINLINE float GetLocationInterpSpeed() const { return LocationInterpSpeed; }

	void SetRelativeXOffset(float Offset, float OffsetLookingUp, float OffsetLookingDown);
	FVector GetCameraComponentWorldLocation() const;
	void SetCameraComponentRelativeXLocation(float RelativeX);
	float GetCameraComponentRelativeXLocation() const;

private:
	void ApplyRelativeXOffsetFromRotation(float Offset, float CameraForwardDotWorldUp);
};
