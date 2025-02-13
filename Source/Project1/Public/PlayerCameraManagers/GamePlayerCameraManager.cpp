// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayerCameraManager.h"
#include "Actors/Cameras/PlayerCamera.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/StreamableManager.h"
#include "GameInstances/Project1GameInstanceBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameViewportClients/Project1GameViewportClientBase.h"

void AGamePlayerCameraManager::AddViewRotation(float Pitch, float Yaw)
{
	AddViewPitch(Pitch);
	AddViewYaw(Yaw);
}

void AGamePlayerCameraManager::AddViewRotation(const FVector2D& InputVector)
{
	AddViewPitch(InputVector.Y);
	AddViewYaw(InputVector.X);
}

void AGamePlayerCameraManager::AddViewYawRotation(float Yaw)
{
	AddViewYaw(Yaw);
}

void AGamePlayerCameraManager::AddImmediateViewRotation(float Pitch, float Yaw)
{
	AddViewPitch(Pitch);
	AddViewYaw(Yaw);

	ViewPitchCurrent = ViewPitchTarget;
	ViewYawCurrent = ViewYawTarget;
}

void AGamePlayerCameraManager::AddImmediateViewRotation(const FVector2D& InputVector)
{
	AddViewPitch(InputVector.Y);
	AddViewYaw(InputVector.X);

	ViewPitchCurrent = ViewPitchTarget;
	ViewYawCurrent = ViewYawTarget;
}

FQuat AGamePlayerCameraManager::GetViewYawOrientation()
{
	if (!IsValid(PlayerCameraActor))
	{
		return FQuat::Identity;
	}

	// Yaw rotation only is applied to the player camera actor. Pitch is applied locally to the camera component's parent component
	return PlayerCameraActor->GetActorForwardVector().ToOrientationQuat();
}

void AGamePlayerCameraManager::ResetViewOrientation()
{
	if (!IsValid(TargetFollowActor))
	{
		return;
	}

	ViewPitchTarget = 0.0f;
	ViewYawTarget = static_cast<float>(TargetFollowActor->GetActorRotation().Yaw);
}

void AGamePlayerCameraManager::UpdateCamera(float DeltaTime)
{
	if (IsValid(PlayerCameraActor))
	{
		UpdateCameraRotation(DeltaTime);
		UpdateCameraLocation(DeltaTime);
		UpdateCameraCollision();
	}

	OnCameraUpdated.Broadcast(ViewPitchCurrent, ViewYawCurrent);

	Super::UpdateCamera(DeltaTime);
}

void AGamePlayerCameraManager::BeginPlay()
{
	Super::BeginPlay();

	// Get world
	World = GetWorld();

	// Load player camera actor class and spawn player camera actor into the world
	if (UKismetSystemLibrary::IsValidSoftClassReference(PlayerCameraActorClass))
	{
		PlayerCameraActorClassStreamableHandle = CastChecked<UProject1GameInstanceBase>(UGameplayStatics::GetGameInstance(this))->GetStreamableManager().RequestAsyncLoad(
			PlayerCameraActorClass.ToSoftObjectPath(),
			FStreamableDelegate::CreateLambda([this]() {
				// Get player pawn
				const TObjectPtr<const APawn> PlayerPawn{ UGameplayStatics::GetPlayerPawn(this, 0) };

				// Loaded player camera actor class. Spawn actor class into the world with the same transform as the player pawn
				FActorSpawnParameters SpawnInfo = {};
				SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
				PlayerCameraActor = GetWorld()->SpawnActor<APlayerCamera>(
					PlayerCameraActorClassStreamableHandle->GetLoadedAsset<UClass>(),
					PlayerPawn->GetActorTransform(),
					SpawnInfo
				);

				// Setup camera probe collision query params
				TArray<const AActor*> CameraProbeIgnoredActors{
					PlayerPawn,
					PlayerCameraActor
				};
				CameraProbeCollisionQueryParams.AddIgnoredActors(CameraProbeIgnoredActors);
				CameraProbeCollisionQueryParams.bTraceComplex = false;

				// Setup camera probe shape
				CameraProbeShape = FCollisionShape::MakeSphere(CameraProbeRadius);

				// Set the spawned player camera actor as the view target
				SetViewTarget(PlayerCameraActor);
				}));
	}
}

void AGamePlayerCameraManager::AddViewPitch(float Pitch)
{
	ViewPitchTarget = FMath::Clamp(ViewPitchTarget + Pitch, ViewPitchMin, ViewPitchMax);
}

void AGamePlayerCameraManager::AddViewYaw(float Yaw)
{
	ViewYawTarget += Yaw;
}

void AGamePlayerCameraManager::UpdateCameraRotation(float DeltaTime)
{
	// Update player camera rotation. Current pitch and yaw values are interpolated as quaternions to ensure that the shortest path is taken during interpolations.
	const float RotationInterpSpeed{ PlayerCameraActor->GetRotateInterpSpeed() };

	ViewPitchCurrent = FMath::QInterpTo(FQuat::MakeFromRotator(FRotator(static_cast<double>(ViewPitchCurrent), 0.0, 0.0)),
		FQuat::MakeFromRotator(FRotator(StaticCast<double>(ViewPitchTarget), 0.0, 0.0)),
		DeltaTime, RotationInterpSpeed).Rotator().Pitch;

	ViewYawCurrent = FMath::QInterpTo(FQuat::MakeFromRotator(FRotator(0.0, static_cast<double>(ViewYawCurrent), 0.0)),
		FQuat::MakeFromRotator(FRotator(0.0, StaticCast<double>(ViewYawTarget), 0.0)),
		DeltaTime, RotationInterpSpeed).Rotator().Yaw;


	// Wrap yaw to prevent overflow
	if (ViewYawCurrent > ViewYawMax)
	{
		ViewYawCurrent = FMath::Wrap(ViewYawCurrent, ViewYawMin, ViewYawMax);
		ViewYawTarget = FMath::Wrap(ViewYawTarget, ViewYawMin, ViewYawMax);
	}
	else if (ViewYawCurrent < ViewYawMin)
	{
		ViewYawCurrent = FMath::Wrap(ViewYawCurrent, ViewYawMin, ViewYawMax);
		ViewYawTarget = FMath::Wrap(ViewYawTarget, ViewYawMin, ViewYawMax);
	}

	PlayerCameraActor->SetRotation(ViewPitchCurrent, ViewYawCurrent);
}

void AGamePlayerCameraManager::UpdateCameraLocation(float DeltaTime)
{
	if (!IsValid(TargetFollowActor))
	{
		return;
	}

	const FVector TargetViewLocation{ TargetFollowActor->GetActorLocation() };
	FVector NewViewLocation{ FMath::VInterpTo(PlayerCameraActor->GetActorLocation(), TargetViewLocation, DeltaTime, PlayerCameraActor->GetLocationInterpSpeed()) };

	// Clamp max horizontal location lag distance from target follow actor if requested
	if (bLimitHorizontalCameraLagDistance)
	{
		const FVector2D HorizontalTargetToViewVector{ (FVector2D(NewViewLocation) - FVector2D(TargetViewLocation)) };
		const double HorizontalDistance{ HorizontalTargetToViewVector.Length() };

		if (HorizontalDistance > StaticCast<double>(MaxHorizontalCameraLagDistanceFromTarget))
		{
			const FVector2D MaxHorizontalViewLocation{ FVector2D(TargetViewLocation) +
				(HorizontalTargetToViewVector.GetSafeNormal() * StaticCast<double>(MaxHorizontalCameraLagDistanceFromTarget)) };

			NewViewLocation.X = MaxHorizontalViewLocation.X;
			NewViewLocation.Y = MaxHorizontalViewLocation.Y;
		}
	}

	// Clamp max vertical location lag distance from target follow actor
	if (bLimitVerticalCameraLagDistance)
	{
		const double VerticalTargetToViewVector{ NewViewLocation.Z - TargetViewLocation.Z };

		if (FMath::Abs(VerticalTargetToViewVector) > StaticCast<double>(MaxVerticalCameraLagDistanceFromTarget))
		{
			const double MaxVerticalViewLocation{ StaticCast<double>(MaxVerticalCameraLagDistanceFromTarget) * FMath::Sign(VerticalTargetToViewVector) };

			NewViewLocation.Z = TargetViewLocation.Z + MaxVerticalViewLocation;
		}
	}

	// Set location
	PlayerCameraActor->SetActorLocation(NewViewLocation);
}

void AGamePlayerCameraManager::UpdateCameraCollision()
{
	// Trace from the camera actor location to the camera component location in world space
	// If collision found move camera component in front of the collision
	const FVector TraceStart{ PlayerCameraActor->GetCameraComponentWorldOrbitPoint()};
	const FVector TraceEnd{ PlayerCameraActor->GetCameraComponentWorldLocation() };
	FHitResult ProbeHitResult{};
	if (World->SweepSingleByChannel(
		ProbeHitResult,
		TraceStart,
		TraceEnd,
		FQuat::Identity,
		CameraProbeCollisionChannel,
		CameraProbeShape,
		CameraProbeCollisionQueryParams
	))
	{
		// Ignore collision if the probe started in penetration
		if (ProbeHitResult.bStartPenetrating)
		{
			return;
		}
		// Probe found a collision. Move camera component in front of collision along probe vector, overriding player camera relative X offset
		PlayerCameraActor->SetCameraComponentWorldLocation(ProbeHitResult.Location);
	}
}
