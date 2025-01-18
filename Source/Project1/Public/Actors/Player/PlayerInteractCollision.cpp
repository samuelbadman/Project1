// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInteractCollision.h"
#include "Components/CapsuleComponent.h"

// Sets default values
APlayerInteractCollision::APlayerInteractCollision()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create capsule collision component
	CapsuleCollision = CreateDefaultSubobject<UCapsuleComponent>(FName(TEXT("CapsuleCollision")));
	RootComponent = CapsuleCollision;
	CapsuleCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}

void APlayerInteractCollision::SetCapsuleCollisionSize(float InRadius, float InHalfHeight)
{
	CapsuleCollision->SetCapsuleSize(InRadius, InHalfHeight);
}
