// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCameraManagers/Project1PlayerCameraManagerBase.h"
#include "GamePlayerCameraManager.generated.h"

class APlayerCamera;
struct FStreamableHandle;

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCameraUpdatedDelegate, float /* CurrentPitch */, float /* CurrentYaw */);

/**
 * 
 */
UCLASS()
class PROJECT1_API AGamePlayerCameraManager : public AProject1PlayerCameraManagerBase
{
	GENERATED_BODY()
	
public:
	FOnCameraUpdatedDelegate OnCameraUpdated{};

private:
	UPROPERTY(EditDefaultsOnly)
	TSoftClassPtr<APlayerCamera> PlayerCameraActorClass{ nullptr };

	UPROPERTY(EditAnywhere)
	bool bLimitHorizontalCameraLagDistance{ false };

	UPROPERTY(EditAnywhere, meta = (EditCondition = "bLimitHorizontalCameraLagDistance"))
	float MaxHorizontalCameraLagDistanceFromTarget{ 10000.0f };

	UPROPERTY(EditAnywhere)
	bool bLimitVerticalCameraLagDistance{ false };

	UPROPERTY(EditAnywhere, meta = (EditCondition = "bLimitVerticalCameraLagDistance"))
	float MaxVerticalCameraLagDistanceFromTarget{ 10000.0f };

	UPROPERTY(EditAnywhere)
	TEnumAsByte<ECollisionChannel> CameraProbeCollisionChannel{ ECC_Camera };

	UPROPERTY(EditAnywhere)
	float CameraProbeRadius{ 15.0f };

	TObjectPtr<UWorld> World{ nullptr };

	TObjectPtr<APlayerCamera> PlayerCameraActor{ nullptr };
	TSharedPtr<FStreamableHandle> PlayerCameraActorClassStreamableHandle{ nullptr };

	float ViewPitchCurrent{ 0.0f };
	float ViewYawCurrent{ 0.0f };
	float ViewPitchTarget{ 0.0f };
	float ViewYawTarget{ 0.0f };

	// The actor the camera manager will place the camera behind in the world on update
	TObjectPtr<const AActor> TargetFollowActor{ nullptr };

	FCollisionQueryParams CameraProbeCollisionQueryParams{};
	FCollisionShape CameraProbeShape{};

	// The actor the camera manager will rotate the camera to look at on update
	TObjectPtr<AActor> ViewLockTargetActor{ nullptr };

public:
	void AddViewRotation(float Pitch, float Yaw);
	void AddViewRotation(const FVector2D& InputVector);
	void AddViewYawRotation(float Yaw);

	// Adds view rotation, immediately applying the rotation to the view, ignoring rotation iterpolation
	void AddImmediateViewRotation(float Pitch, float Yaw);

	// Adds view rotation, immediately applying the rotation to the view, ignoring rotation iterpolation
	void AddImmediateViewRotation(const FVector2D& InputVector);

	FQuat GetViewYawOrientation();
	void ResetViewOrientation();

	FVector GetViewWorldLocation() const;

	void SetTargetFollowActor(TObjectPtr<AActor> TargetActor);

	void LockViewToTarget(TObjectPtr<AActor> Target);
	void ClearViewLockTarget();
	bool IsViewLocked() const;
	TObjectPtr<AActor> GetViewLockTarget() const;

private:
	/**
	 * Performs per-tick camera update. Called once per tick after all other actors have been ticked.
	 */
	void UpdateCamera(float DeltaTime) override;

	void BeginPlay() override;

	void AddViewPitch(float Pitch);
	void AddViewYaw(float Yaw);
	void UpdateCameraRotation(float DeltaTime);
	void UpdateCameraLocation(float DeltaTime);
	void UpdateCameraCollision();
};
