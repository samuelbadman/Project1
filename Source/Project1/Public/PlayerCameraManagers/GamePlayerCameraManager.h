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

	float ViewPitchCurrent{ 0.0f };
	float ViewYawCurrent{ 0.0f };
	float ViewPitchTarget{ 0.0f };
	float ViewYawTarget{ 0.0f };

	bool bInterpolateCameraRotation{ true };

	TObjectPtr<const AActor> TargetFollowActor{ nullptr };

public:
	void AddViewRotation(float Pitch, float Yaw);
	void AddViewRotationFromInput(const FVector2D& InputVector);
	void AddViewYawRotation(float Yaw);
	FQuat GetViewYawOrientation();

	FORCEINLINE void SetTargetFollowActor(TObjectPtr<const AActor> TargetActor) { TargetFollowActor = TargetActor; }

private:
	/**
	 * Performs per-tick camera update. Called once per tick after all other actors have been ticked.
	 */
	void UpdateCamera(float DeltaTime) override;

	void BeginPlay() override;

	void AddViewPitch(float Pitch);
	void AddViewYaw(float Yaw);
};
