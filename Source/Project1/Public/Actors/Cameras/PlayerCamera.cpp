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
	RelativeXOffset = -300.0f;
	RelativeXOffsetLookingUp = -50.0f;
	RelativeXOffsetLookingDown = -400.0f;
	RelativeXOffsetAdjustmentInterpSpeed = 2.0f;
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

FVector APlayerCamera::GetCameraComponentWorldOrbitPoint() const
{
	return (GetActorLocation() + CameraComponentOffset);
}

FVector APlayerCamera::GetCameraComponentWorldLocation() const
{
	// Get the camera rotation yaw from the actor and pitch from the camera parent component
	const FRotator CameraRotation(CameraParentComponent->GetComponentRotation().Pitch, GetActorRotation().Yaw, 0.0f);
	const FVector CameraBackVector{ CameraRotation.Vector() };
	return (GetCameraComponentWorldOrbitPoint() + (CameraBackVector * RelativeXOffset));
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

void APlayerCamera::ApplyRelativeXOffsetFromRotation(float Offset, float CameraForwardDotWorldUp, float DeltaTime)
{
	FVector RelativeLocation{ CameraComponent->GetRelativeLocation() };
	RelativeLocation.X = FMath::FInterpTo(
		RelativeLocation.X,
		FMath::Lerp(RelativeXOffset, Offset, FMath::Abs(CameraForwardDotWorldUp)),
		DeltaTime,
		RelativeXOffsetAdjustmentInterpSpeed);
	CameraComponent->SetRelativeLocation(RelativeLocation);
}

FVector APlayerCamera::CalculateCameraComponentRelativeLocation() const
{
	const FVector WorldCameraComponentLocation{ GetActorLocation() + CameraComponentOffset };
	FVector RelativeCameraComponentLocation{ UKismetMathLibrary::InverseTransformLocation(GetActorTransform(), WorldCameraComponentLocation) };
	RelativeCameraComponentLocation.X += RelativeXOffset;
	return RelativeCameraComponentLocation;
}
