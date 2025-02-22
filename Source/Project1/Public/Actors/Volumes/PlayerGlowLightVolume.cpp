// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerGlowLightVolume.h"
#include "Components/BoxComponent.h"
#include "FunctionLibraries/Project1GameplayLibrary.h"
#include "Pawns/Characters/PlayerCharacterBase.h"

// Sets default values
APlayerGlowLightVolume::APlayerGlowLightVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionVolume = CreateDefaultSubobject<UBoxComponent>(FName(TEXT("CollisionVolume")));
	CollisionVolume->OnComponentBeginOverlap.AddDynamic(this, &APlayerGlowLightVolume::OnComponentBeginOverlap);
	CollisionVolume->OnComponentEndOverlap.AddDynamic(this, &APlayerGlowLightVolume::OnComponentEndOverlap);
}

void APlayerGlowLightVolume::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult)
{
	if (UProject1GameplayLibrary::IsPlayerCharacter(this, OtherActor))
	{
		const TObjectPtr<APlayerCharacterBase> PlayerCharacter{ CastChecked<APlayerCharacterBase>(OtherActor) };
		PlayerCharacter->SetGlowLightVisibility(true);
	}
}

void APlayerGlowLightVolume::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (UProject1GameplayLibrary::IsPlayerCharacter(this, OtherActor))
	{
		const TObjectPtr<APlayerCharacterBase> PlayerCharacter{ CastChecked<APlayerCharacterBase>(OtherActor) };
		PlayerCharacter->SetGlowLightVisibility(false);
	}
}

