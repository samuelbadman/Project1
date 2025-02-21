// Fill out your copyright notice in the Description page of Project Settings.


#include "Proj1CharacterMovementComponent.h"
#include "Pawns/Characters/Project1CharacterBase.h"

UProj1CharacterMovementComponent::UProj1CharacterMovementComponent()
{
	Project1Character = nullptr;
}

void UProj1CharacterMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	// Get owner project 1 character
	Project1Character = CastChecked<AProject1CharacterBase>(GetOwner());
}

void UProj1CharacterMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::White, FString::Printf(TEXT("[%s] RequestDirectMove"), *GetOwner()->GetName()));
	DrawDebugDirectionalArrow(GetWorld(), GetOwner()->GetActorLocation(), GetOwner()->GetActorLocation() + (MoveVelocity.GetSafeNormal() * 100.0f), 10.0f, FColor::Cyan);
	Project1Character->Move(MoveVelocity.GetSafeNormal());
}
