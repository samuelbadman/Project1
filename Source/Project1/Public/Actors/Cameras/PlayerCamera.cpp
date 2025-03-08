// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCamera.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"

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

	// Set default values
	CameraComponentOffset = FVector::ZeroVector;
	TargetRelativeXOffsetHorizontal = -300.0f;
	TargetRelativeXOffsetUp = -50.0f;
	TargetRelativeXOffsetDown = -400.0f;
	RelativeXOffsetAdjustmentInterpSpeed = 2.0f;
}

void APlayerCamera::SetRotation(float Pitch, float Yaw)
{
	// Separate pitch and yaw to avoid gimbal lock. Pitch is applied locally to the camera parent component and yaw is applied to the actor in world space
	CameraParentComponent->SetRelativeRotation(FRotator(StaticCast<double>(Pitch), 0.0, 0.0));
	SetActorRotation(FRotator(0.0, StaticCast<double>(Yaw), 0.0));

	// Update player camera relative X offset for pitch angle
	const double CameraForwardDotWorldUp{ -FVector::DotProduct(CameraParentComponent->GetRelativeRotation().Vector(), FVector::UpVector) };
	ApplyRelativeXOffsetFromRotation((CameraForwardDotWorldUp < 0.0) ? TargetRelativeXOffsetUp : TargetRelativeXOffsetDown, CameraForwardDotWorldUp, GetWorld()->GetDeltaSeconds());
}

void APlayerCamera::SetTargetRelativeXOffset(float NewOffsetHorizontal, float NewOffsetUp, float NewOffsetDown)
{
	TargetRelativeXOffsetHorizontal = NewOffsetHorizontal;
	TargetRelativeXOffsetUp = NewOffsetUp;
	TargetRelativeXOffsetDown = NewOffsetDown;
}

FVector APlayerCamera::GetCameraComponentWorldOrbitPoint() const
{
	return (GetActorLocation() + CameraComponentOffset);
}

FVector APlayerCamera::GetCameraComponentWorldLocation() const
{
	return CameraComponent->GetComponentLocation();
}

void APlayerCamera::SetCameraComponentWorldLocation(const FVector& Location)
{
	CameraComponent->SetWorldLocation(Location);
}

void APlayerCamera::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	CameraComponent->SetRelativeLocation(CalculateCameraComponentRelativeLocation());
}

void APlayerCamera::ApplyRelativeXOffsetFromRotation(float TargetOffset, float CameraForwardDotWorldUp, float DeltaTime)
{
	FVector RelativeLocation{ CameraComponent->GetRelativeLocation() };
	RelativeLocation.X = FMath::FInterpTo(
		RelativeLocation.X,
		CalculateCameraRelativeXOffset(TargetOffset, CameraForwardDotWorldUp),
		DeltaTime,
		RelativeXOffsetAdjustmentInterpSpeed);
	CameraComponent->SetRelativeLocation(RelativeLocation);
}

FVector APlayerCamera::CalculateCameraComponentRelativeLocation() const
{
	const FVector WorldCameraComponentLocation{ GetActorLocation() + CameraComponentOffset };
	FVector RelativeCameraComponentLocation{ UKismetMathLibrary::InverseTransformLocation(GetActorTransform(), WorldCameraComponentLocation) };
	RelativeCameraComponentLocation.X += TargetRelativeXOffsetHorizontal;
	return RelativeCameraComponentLocation;
}

float APlayerCamera::CalculateCameraRelativeXOffset(float TargetRelativeXOffset, float CameraForwardDotWorldUp) const
{
	return FMath::Lerp(TargetRelativeXOffsetHorizontal, TargetRelativeXOffset, FMath::Abs(CameraForwardDotWorldUp));
}

float APlayerCamera::GetTargetRelativeXOffset(float CameraForwardDotWorldUp) const
{
	return (CameraForwardDotWorldUp < 0.0) ? TargetRelativeXOffsetUp : TargetRelativeXOffsetDown;
}

float APlayerCamera::GetCameraForwardDotWorldUp() const
{
	return -FVector::DotProduct(CameraParentComponent->GetRelativeRotation().Vector(), FVector::UpVector);
}
