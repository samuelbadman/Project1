// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponents/Project1ActorComponentBase.h"
#include "PlayerInteractComponent.generated.h"

class APlayerInteractCollision;
class IInteractable;
struct FInputActionValue;

DECLARE_MULTICAST_DELEGATE_TwoParams(FBeginInteractableOverlapDelegateSignature, TWeakObjectPtr<AActor> /* Interactable */, int32 /* NumOverlappedInteractables */);
DECLARE_MULTICAST_DELEGATE_TwoParams(FEndInteractableOverlapDelegateSignature, TWeakObjectPtr<AActor> /* Interactable */, int32 /* NumOverlappedInteractables */);
DECLARE_MULTICAST_DELEGATE_OneParam(FTargetInteractableChangedDelegateSignature, TWeakObjectPtr<AActor> /* NewTargetInteractable */);

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
	FTargetInteractableChangedDelegateSignature OnTargetInteractableChangedDelegate{};

private:
	UPROPERTY(EditDefaultsOnly)
	float InteractCollisionRadiusMultiplier{ 2.0f };

	UPROPERTY(EditDefaultsOnly)
	float InteractCollisionHalfHeightMultiplier{ 1.0f };

	TObjectPtr<APawn> InteractingPawn{ nullptr };
	TObjectPtr<APlayerInteractCollision> PlayerInteractCollisionActor{ nullptr };
	TArray<TObjectPtr<AActor>> OverlappedInteractables{};
	int32 TargetOverlappedInteractableIndex{ INDEX_NONE };

public:
	void SetupNewPawn(TObjectPtr<APawn> Pawn);
	TObjectPtr<AActor> GetTargetInteractable() const;
	void IncrementTargetInteractableIndex(int32 Increment);
	int32 GetNumOverlappedInteractables() const;

	UFUNCTION(BlueprintCallable)
	void EnableInteract();

	UFUNCTION(BlueprintCallable)
	void DisableInteract();

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

	void SetTargetOverlappedInteractable(int32 NewIndex);
};
