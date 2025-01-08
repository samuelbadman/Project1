// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayerCameraManager.h"
#include "Actors/Cameras/PlayerCamera.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/StreamableManager.h"
#include "GameInstances/Project1GameInstanceBase.h"
#include "Kismet/GameplayStatics.h"

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

void AGamePlayerCameraManager::UpdateCamera(float DeltaTime)
{
	Super::UpdateCamera(DeltaTime);

	if (IsValid(PlayerCameraActor))
	{
		// Update player camera rotation. Current pitch and yaw values are interpolated as quaternions to ensure that the shortest path is taken during interpolations.
		const float RotationInterpSpeed{ PlayerCameraActor->GetRotateInterpSpeed() };

		ViewPitchCurrent = FMath::QInterpTo(FQuat::MakeFromRotator(FRotator(static_cast<double>(ViewPitchCurrent), 0.0, 0.0)),
			FQuat::MakeFromRotator(FRotator(static_cast<double>(ViewPitchTarget), 0.0, 0.0)),
			DeltaTime, RotationInterpSpeed).Rotator().Pitch;

		// Wrap yaw to prevent overflow
		ViewYawCurrent = FMath::QInterpTo(FQuat::MakeFromRotator(FRotator(0.0, static_cast<double>(ViewYawCurrent), 0.0)),
			FQuat::MakeFromRotator(FRotator(0.0, static_cast<double>(ViewYawTarget), 0.0)),
			DeltaTime, RotationInterpSpeed).Rotator().Yaw;

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
}

//if (IsValid(ThirdPersonPlayerCamera))
//{
//	// Update third person player camera location
//	if (IsValid(FollowActorTarget))
//	{
//		const FVector TargetLocation = FollowActorTarget->GetActorLocation();
//		FVector NewLocation = FMath::VInterpTo(ThirdPersonPlayerCamera->GetActorLocation(), TargetLocation, DeltaSeconds, ViewLocationInterpSpeed);
//
//		// Clamp max location lag distance
//		FVector TargetToViewVector = (NewLocation - TargetLocation);
//		const double Distance = TargetToViewVector.Length();
//
//		TargetToViewVector.Normalize();
//		if (Distance > static_cast<double>(MaxViewLocationLagDistance))
//		{
//			NewLocation = TargetLocation + (TargetToViewVector * static_cast<double>(MaxViewLocationLagDistance));
//		}
//
//		// Set location
//		ThirdPersonPlayerCamera->SetActorLocation(NewLocation);
//	}
//
//	// Update third person player camera rotation. Current pitch and yaw values are interpolated as quaternions to ensure that the shortest path is taken during interpolations.
//	const TObjectPtr<USpringArmComponent> SpringArm = ThirdPersonPlayerCamera->GetSpringArm();
//
//	ViewPitchCurrent = FMath::QInterpTo(FQuat::MakeFromRotator(FRotator(static_cast<double>(ViewPitchCurrent), 0.0, 0.0)),
//		FQuat::MakeFromRotator(FRotator(static_cast<double>(ViewPitchTarget), 0.0, 0.0)),
//		DeltaSeconds, ViewRotationInterpSpeed).Rotator().Pitch;
//
//	// Wrap yaw to prevent overflow
//	ViewYawCurrent = FMath::QInterpTo(FQuat::MakeFromRotator(FRotator(0.0, static_cast<double>(ViewYawCurrent), 0.0)),
//		FQuat::MakeFromRotator(FRotator(0.0, static_cast<double>(ViewYawTarget), 0.0)),
//		DeltaSeconds, ViewRotationInterpSpeed).Rotator().Yaw;
//
//	if (ViewYawCurrent > ViewYawMax)
//	{
//		ViewYawCurrent = FMath::Wrap(ViewYawCurrent, ViewYawMin, ViewYawMax);
//		ViewYawTarget = FMath::Wrap(ViewYawTarget, ViewYawMin, ViewYawMax);
//	}
//	else if (ViewYawCurrent < ViewYawMin)
//	{
//		ViewYawCurrent = FMath::Wrap(ViewYawCurrent, ViewYawMin, ViewYawMax);
//		ViewYawTarget = FMath::Wrap(ViewYawTarget, ViewYawMin, ViewYawMax);
//	}
//
//	// Separate pitch and yaw to avoid gimbal lock. Pitch is applied locally to the spring arm component and yaw is applied to the actor in world space
//	SpringArm->SetRelativeRotation(FRotator(static_cast<double>(ViewPitchCurrent), 0.0, 0.0));
//	ThirdPersonPlayerCamera->SetActorRotation(FRotator(0.0, static_cast<double>(ViewYawCurrent), 0.0));
//
//	// Update third person player camera spring arm length for pitch angle
//	const double CameraForwardDotWorldUp = -FVector::DotProduct(SpringArm->GetRelativeRotation().Vector(), FVector::UpVector);
//	if (CameraForwardDotWorldUp < 0.0)
//	{
//		SpringArm->TargetArmLength = FMath::Lerp(ThirdPersonPlayerCamera->GetSpringArmLength(), ThirdPersonPlayerCamera->GetSpringArmLengthLookUp(), FMath::Abs(CameraForwardDotWorldUp));
//	}
//	else
//	{
//		SpringArm->TargetArmLength = FMath::Lerp(ThirdPersonPlayerCamera->GetSpringArmLength(), ThirdPersonPlayerCamera->GetSpringArmLengthLookDown(), CameraForwardDotWorldUp);
//	}
//
//	// Broadcast delegate
//	OnViewUpdated.Broadcast();
//}



void AGamePlayerCameraManager::BeginPlay()
{
	Super::BeginPlay();

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
