// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponents/Project1ActorComponentBase.h"
#include "PlayerInteractComponent.generated.h"

class APlayerInteractCollision;
class IInteractable;

DECLARE_MULTICAST_DELEGATE_TwoParams(FBeginInteractableOverlapDelegateSignature, TWeakObjectPtr<AActor> /* Interactable */, int32 /* NumOverlappedInteractables */);
DECLARE_MULTICAST_DELEGATE_TwoParams(FEndInteractableOverlapDelegateSignature, TWeakObjectPtr<AActor> /* Interactable */, int32 /* NumOverlappedInteractables */);

/**
 * 
 */
UCLASS()
class PROJECT1_API UPlayerInteractComponent : public UProject1ActorComponentBase
{
	GENERATED_BODY()
	
public:
	FBeginInteractableOverlapDelegateSignature OnBeginInteractableOverlapDelegate{};
	FEndInteractableOverlapDelegateSignature OnEndInteractableOverlapDelegate{};

private:
	UPROPERTY(EditDefaultsOnly)
	float InteractCollisionRadiusMultiplier{ 2.0f };

	UPROPERTY(EditDefaultsOnly)
	float InteractCollisionHalfHeightMultiplier{ 1.0f };

	TObjectPtr<APawn> InteractingPawn{ nullptr };
	TObjectPtr<APlayerInteractCollision> PlayerInteractCollisionActor{ nullptr };
	TArray<TObjectPtr<AActor>> OverlappedInteractables{};

public:
	void SetupNewPawn(TObjectPtr<APawn> Pawn);
	void OnInteractInput();

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
