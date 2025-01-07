// Fill out your copyright notice in the Description page of Project Settings.


#include "Project1ActorBase.h"

// Sets default values
AProject1ActorBase::AProject1ActorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AProject1ActorBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProject1ActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

