// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCamera.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

APlayerCamera::APlayerCamera()
{
	PrimaryActorTick.bCanEverTick = false;

	// Create scene component and set as root component other components will be attached to
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = SceneComponent;

	// Create scene component and parent to the root component. This component is the parent of the camera component
	CameraParentComponent = CreateDefaultSubobject<USceneComponent>(TEXT("CameraParentComponent"));
	CameraParentComponent->SetupAttachment(RootComponent);

	// Create camera component and attach to parent scene component. This allows the camera component to be offset back and rotate around the actor root
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(CameraParentComponent);
}

void APlayerCamera::SetRotation(float Pitch, float Yaw)
{
	// Separate pitch and yaw to avoid gimbal lock. Pitch is applied locally to the camera parent component and yaw is applied to the actor in world space
	CameraParentComponent->SetRelativeRotation(FRotator(StaticCast<double>(Pitch), 0.0, 0.0));
	SetActorRotation(FRotator(0.0, StaticCast<double>(Yaw), 0.0));

	// Update player camera relative X offset for pitch angle
	const double CameraForwardDotWorldUp{ -FVector::DotProduct(CameraParentComponent->GetRelativeRotation().Vector(), FVector::UpVector) };
	ApplyRelativeXOffsetFromRotation((CameraForwardDotWorldUp < 0.0) ? RelativeXOffsetLookingUp : RelativeXOffsetLookingDown, CameraForwardDotWorldUp, GetWorld()->GetDeltaSeconds());
}

void APlayerCamera::SetRelativeXOffset(float Offset, float OffsetLookingUp, float OffsetLookingDown)
{
	RelativeXOffset = Offset;
	RelativeXOffsetLookingUp = OffsetLookingUp;
	RelativeXOffsetLookingDown = OffsetLookingDown;
}

FVector APlayerCamera::GetCameraComponentWorldLocation() const
{
	return CameraComponent->GetComponentLocation();
}

void APlayerCamera::SetCameraComponentRelativeXLocation(float RelativeX)
{
	CameraComponent->SetRelativeLocation(FVector(RelativeX, 0.0, 0.0));
}

float APlayerCamera::GetCameraComponentRelativeXLocation() const
{
	return CameraComponent->GetRelativeLocation().X;
}

void APlayerCamera::ApplyRelativeXOffsetFromRotation(float Offset, float CameraForwardDotWorldUp, float DeltaTime)
{
	CameraComponent->SetRelativeLocation(FVector(
		FMath::FInterpTo(
			CameraComponent->GetRelativeLocation().X,
			FMath::Lerp(RelativeXOffset, Offset, FMath::Abs(CameraForwardDotWorldUp)),
			DeltaTime,
			RelativeXOffsetAdjustmentInterpSpeed
		),
		0.0,
		0.0
	));
}
