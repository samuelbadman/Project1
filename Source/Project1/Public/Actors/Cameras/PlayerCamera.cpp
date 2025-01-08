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

	// Create spring arm component and attach to root component
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);

	// Create camera component and attach to spring arm component
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);
}
