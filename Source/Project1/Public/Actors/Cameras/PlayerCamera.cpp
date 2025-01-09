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

	// Create spring arm component and attach to root component. 
	// Inherit yaw from the component's parent as yaw rotation is only applied to the actor root.
	// Do not inherit pitch as pitch is only applied to the spring arm component
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bInheritPitch = false;
	SpringArmComponent->bInheritYaw = true;

	// Create camera component and attach to spring arm component
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void APlayerCamera::Rotate(float Pitch, float Yaw)
{
	// Separate pitch and yaw to avoid gimbal lock. Pitch is applied locally to the spring arm component and yaw is applied to the actor in world space
	SpringArmComponent->SetRelativeRotation(FRotator(StaticCast<double>(Pitch), 0.0, 0.0));
	SetActorRotation(FRotator(0.0, StaticCast<double>(Yaw), 0.0));

	// Update player camera spring arm length for pitch angle
	const double CameraForwardDotWorldUp = -FVector::DotProduct(SpringArmComponent->GetRelativeRotation().Vector(), FVector::UpVector);
	if (CameraForwardDotWorldUp < 0.0)
	{
		SpringArmComponent->TargetArmLength = FMath::Lerp(CachedSpringArmTargetArmLength, SpringArmLengthLookingUp, FMath::Abs(CameraForwardDotWorldUp));
	}
	else
	{
		SpringArmComponent->TargetArmLength = FMath::Lerp(CachedSpringArmTargetArmLength, SpringArmLengthLookingDown, CameraForwardDotWorldUp);
	}
}

void APlayerCamera::BeginPlay()
{
	Super::BeginPlay();

	// Cache the target arm length
	CachedSpringArmTargetArmLength = SpringArmComponent->TargetArmLength;
}
