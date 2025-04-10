// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ArtificialPlayerLightTriggerVolume.generated.h"

class UBoxComponent;
class AGamePlayerController;

UCLASS()
class PROJECT1_API AArtificialPlayerLightTriggerVolume : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> CollisionVolume;

	TObjectPtr<AGamePlayerController> GamePlayerController;

public:	
	// Sets default values for this actor's properties
	AArtificialPlayerLightTriggerVolume();

protected:
	void BeginPlay() override;

private:
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult& SweepResult);

	UFUNCTION()
	void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
