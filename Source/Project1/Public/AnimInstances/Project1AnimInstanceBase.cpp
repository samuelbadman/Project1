// Fill out your copyright notice in the Description page of Project Settings.


#include "Project1AnimInstanceBase.h"

UProject1AnimInstanceBase::UProject1AnimInstanceBase()
	: Project1CharacterOwner(nullptr)
{
}

void UProject1AnimInstanceBase::NativeInitializeAnimation()
{
	Project1CharacterOwner = Cast<AProject1CharacterBase>(TryGetPawnOwner());
}
