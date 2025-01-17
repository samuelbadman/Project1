// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponents/Project1ActorComponentBase.h"
#include "PlayerInteractComponent.generated.h"

class IInteractable;

/**
 * 
 */
UCLASS()
class PROJECT1_API UPlayerInteractComponent : public UProject1ActorComponentBase
{
	GENERATED_BODY()
	
private:
	TArray<TScriptInterface<IInteractable>> OverlappedInteractables{};

public:
	void SetupNewPawn(TObjectPtr<APawn> Pawn);

private:
	UFUNCTION()
	void OnPawnCollisionBeginOverlap(
		UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult& SweepResult);

	UFUNCTION()
	void OnPawnCollisionEndOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);
};
