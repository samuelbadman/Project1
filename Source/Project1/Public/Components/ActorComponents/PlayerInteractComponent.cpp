// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInteractComponent.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Interfaces/Interactable.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Actors/Player/PlayerInteractCollision.h"
#include "FunctionLibraries/Project1BlueprintFunctionLibrary.h"

void UPlayerInteractComponent::SetupNewPawn(TObjectPtr<APawn> Pawn)
{
	// Cache actor that will be interacting with the world
	InteractingPawn = Pawn;

	// Get pawn as character
	TObjectPtr<ACharacter> Character{ CastChecked<ACharacter>(Pawn) };

	// Get root collision shape component from character
	const TObjectPtr<UCapsuleComponent> PlayerMovementCollision{ Character->GetCapsuleComponent() };

	// Setup player collision actor
	const float InteractCollisionRadius{ PlayerMovementCollision->GetScaledCapsuleRadius() * InteractCollisionRadiusMultiplier };
	const float InteractCollisionHalfHeight{ PlayerMovementCollision->GetScaledCapsuleHalfHeight() * InteractCollisionHalfHeightMultiplier };

	if (!IsValid(PlayerInteractCollisionActor))
	{
		// Player interact collision is not valid. Spawn player interact collision in front of player pawn
		const FVector CharacterLocation{ Character->GetActorLocation() };
		const FRotator CharacterOrientation{ Character->GetActorRotation() };
		const FVector SpawnLocation{ CharacterLocation + (CharacterOrientation.Vector() * InteractCollisionRadius) };
		PlayerInteractCollisionActor = GetWorld()->SpawnActor<APlayerInteractCollision>(APlayerInteractCollision::StaticClass(), SpawnLocation, CharacterOrientation);

		// Bind to shape component overlap events
		UCapsuleComponent& PlayerInteractCollision{ *(PlayerInteractCollisionActor->GetCapsuleCollision()) };
		PlayerInteractCollision.OnComponentBeginOverlap.AddDynamic(this, &UPlayerInteractComponent::OnPawnCollisionBeginOverlap);
		PlayerInteractCollision.OnComponentEndOverlap.AddDynamic(this, &UPlayerInteractComponent::OnPawnCollisionEndOverlap);
	}

	// Resize player interact collision
	PlayerInteractCollisionActor->SetCapsuleCollisionSize(InteractCollisionRadius, InteractCollisionHalfHeight);

	// Attach player interact collision to player pawn, snapping to its transform
	PlayerInteractCollisionActor->AttachToComponent(PlayerMovementCollision, FAttachmentTransformRules::KeepWorldTransform);
}

TObjectPtr<AActor> UPlayerInteractComponent::GetTargetInteractable() const
{
	if (!OverlappedInteractables.IsValidIndex(TargetOverlappedInteractableIndex))
	{
		return nullptr;
	}

	return OverlappedInteractables[TargetOverlappedInteractableIndex];
}

void UPlayerInteractComponent::IncrementTargetInteractableIndex(int32 Increment)
{
	SetTargetOverlappedInteractable(UProject1BlueprintFunctionLibrary::WrapIncrementArrayIndex(
		TargetOverlappedInteractableIndex,
		OverlappedInteractables.Num(),
		Increment
	));
}

int32 UPlayerInteractComponent::GetNumOverlappedInteractables() const
{
	return OverlappedInteractables.Num();
}

void UPlayerInteractComponent::DisableInteract()
{
	PlayerInteractCollisionActor->GetCapsuleCollision()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void UPlayerInteractComponent::EnableInteract()
{
	PlayerInteractCollisionActor->GetCapsuleCollision()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void UPlayerInteractComponent::OnPawnCollisionBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	// Is the overlapping actor interactable?
	if (UKismetSystemLibrary::DoesImplementInterface(OtherActor, UInteractable::StaticClass()))
	{
		// Add interactable to player interactable overlapped list
		OverlappedInteractables.Add(OtherActor);

		// Update target interactable index. Don't update if there is already an interactable targeted
		if (OverlappedInteractables.Num() == 1)
		{
			SetTargetOverlappedInteractable(0);
		}

		// Notify interactable it has become overlapped by the player
		IInteractable::Execute_OnPlayerInteractBeginOverlap(OtherActor);

		// Call subscribed events for when an interactable is overlapped by the player
		OnBeginInteractableOverlapDelegate.Broadcast(OtherActor, OverlappedInteractables.Num());
	}
}

void UPlayerInteractComponent::OnPawnCollisionEndOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (UKismetSystemLibrary::DoesImplementInterface(OtherActor, UInteractable::StaticClass()))
	{
		// If the actor being removed is the current overlapped interactable target
		const bool RemovedTargetOverlappedInteractable{ OtherActor == OverlappedInteractables[TargetOverlappedInteractableIndex] };

		// Remove the interactable from player interactable overlapped list
		OverlappedInteractables.Remove(OtherActor);

		// If the target overlapped interactable index is no longer valid
		// Else if the target index is still valid but the current target interactable was removed
		if (!OverlappedInteractables.IsValidIndex(TargetOverlappedInteractableIndex))
		{
			// Update the target index to be the first overlapped interactable
			SetTargetOverlappedInteractable(0);
		}
		else if (RemovedTargetOverlappedInteractable)
		{
			// Update the target index to be the current index, calling the target interactable changed delegate
			SetTargetOverlappedInteractable(TargetOverlappedInteractableIndex);
		}

		// Notify interactable it has left player interact collision
		IInteractable::Execute_OnPlayerInteractEndOverlap(OtherActor);

		// Call subscribed events for when an interactable has left player interact collision
		OnEndInteractableOverlapDelegate.Broadcast(OtherActor, OverlappedInteractables.Num());
	}
}

void UPlayerInteractComponent::SetTargetOverlappedInteractable(int32 NewIndex)
{
	TargetOverlappedInteractableIndex = NewIndex;

	if (OverlappedInteractables.IsValidIndex(NewIndex))
	{
		OnTargetInteractableChangedDelegate.Broadcast(OverlappedInteractables[NewIndex]);
	}
}
