// Fill out your copyright notice in the Description page of Project Settings.


#include "TestAICharacter.h"

void ATestAICharacter::Move(const FVector& DesiredDirection)
{
	Super::Move(DesiredDirection);
	AddMovementInput(GetActorForwardVector());
}
