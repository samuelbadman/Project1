// Fill out your copyright notice in the Description page of Project Settings.


#include "ArtificialPlayerLightTriggerVolume.h"
#include "Components/BoxComponent.h"
#include "FunctionLibraries/Project1GameplayLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Controllers/PlayerControllers/GamePlayerController.h"

// Sets default values
AArtificialPlayerLightTriggerVolume::AArtificialPlayerLightTriggerVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionVolume = CreateDefaultSubobject<UBoxComponent>(FName(TEXT("CollisionVolume")));
	CollisionVolume->OnComponentBeginOverlap.AddDynamic(this, &AArtificialPlayerLightTriggerVolume::OnComponentBeginOverlap);
	CollisionVolume->OnComponentEndOverlap.AddDynamic(this, &AArtificialPlayerLightTriggerVolume::OnComponentEndOverlap);
}

void AArtificialPlayerLightTriggerVolume::BeginPlay()
{
	Super::BeginPlay();

	GamePlayerController = CastChecked<AGamePlayerController>(UGameplayStatics::GetPlayerController(this, 0));
}

void AArtificialPlayerLightTriggerVolume::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult)
{
	if (UProject1GameplayLibrary::IsActorPlayerCharacter(this, OtherActor))
	{
		GamePlayerController->ActivateArtificialPlayerLight(true);
	}
}

void AArtificialPlayerLightTriggerVolume::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (UProject1GameplayLibrary::IsActorPlayerCharacter(this, OtherActor))
	{
		GamePlayerController->ActivateArtificialPlayerLight(false);
	}
}

