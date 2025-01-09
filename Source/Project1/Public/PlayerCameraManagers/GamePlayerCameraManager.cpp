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

void AGamePlayerCameraManager::AddViewRotationFromInput(const FVector2D& InputVector)
{
	AddViewPitch(InputVector.Y);
	AddViewYaw(InputVector.X);
}

void AGamePlayerCameraManager::AddViewYawRotation(float Yaw)
{
	AddViewYaw(Yaw);
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

void AGamePlayerCameraManager::UpdateCamera(float DeltaTime)
{
	if (IsValid(PlayerCameraActor))
	{
		UpdateCameraRotation(DeltaTime);
		UpdateCameraLocation(DeltaTime);
	}

	Super::UpdateCamera(DeltaTime);
}

void AGamePlayerCameraManager::BeginPlay()
{
	Super::BeginPlay();

	// Bind to input device changed event
	CastChecked<UProject1GameViewportClientBase>(GetWorld()->GetGameViewport())->GetOnInputDeviceChangedDelegate().AddLambda([this](bool UsingGamepad) {
		bInterpolateCameraRotation = UsingGamepad;
		});

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

	if (bInterpolateCameraRotation)
	{
		ViewPitchCurrent = FMath::QInterpTo(FQuat::MakeFromRotator(FRotator(static_cast<double>(ViewPitchCurrent), 0.0, 0.0)),
			FQuat::MakeFromRotator(FRotator(StaticCast<double>(ViewPitchTarget), 0.0, 0.0)),
			DeltaTime, RotationInterpSpeed).Rotator().Pitch;

		ViewYawCurrent = FMath::QInterpTo(FQuat::MakeFromRotator(FRotator(0.0, static_cast<double>(ViewYawCurrent), 0.0)),
			FQuat::MakeFromRotator(FRotator(0.0, StaticCast<double>(ViewYawTarget), 0.0)),
			DeltaTime, RotationInterpSpeed).Rotator().Yaw;
	}
	else
	{
		ViewPitchCurrent = StaticCast<double>(ViewPitchTarget);
		ViewYawCurrent = StaticCast<double>(ViewYawTarget);
	}

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

	PlayerCameraActor->Rotate(ViewPitchCurrent, ViewYawCurrent);
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

	// TODO: Clamp max vertical location lag distance from target follow actor

	// Set location
	PlayerCameraActor->SetActorLocation(NewViewLocation);
}
