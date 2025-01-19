// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInteractComponent.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Interfaces/Interactable.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Actors/Player/PlayerInteractCollision.h"

void UPlayerInteractComponent::SetupNewPawn(TObjectPtr<APawn> Pawn)
{
	// Cache actor that will be interacting with the world
	InteractingPawn = Pawn;

	// Get pawn as character
	TObjectPtr<ACharacter> Character{ CastChecked<ACharacter>(Pawn) };

	// Get root collision shape component from character
	const TObjectPtr<UCapsuleComponent> PlayerMovementCollision{ Character->GetCapsuleComponent() };

	// Setup player collision actor
	if (!IsValid(PlayerInteractCollisionActor))
	{
		// Player interact collision is not valid. Spawn player interact collision at player pawn
		PlayerInteractCollisionActor = GetWorld()->SpawnActor<APlayerInteractCollision>(APlayerInteractCollision::StaticClass(), Character->GetActorTransform());

		// Bind to shape component overlap events
		UCapsuleComponent& PlayerInteractCollision{ *(PlayerInteractCollisionActor->GetCapsuleCollision()) };
		PlayerInteractCollision.OnComponentBeginOverlap.AddDynamic(this, &UPlayerInteractComponent::OnPawnCollisionBeginOverlap);
		PlayerInteractCollision.OnComponentEndOverlap.AddDynamic(this, &UPlayerInteractComponent::OnPawnCollisionEndOverlap);
	}

	// Resize player interact collision
	PlayerInteractCollisionActor->SetCapsuleCollisionSize(
		PlayerMovementCollision->GetUnscaledCapsuleRadius() * InteractCollisionRadiusMultiplier,
		PlayerMovementCollision->GetUnscaledCapsuleHalfHeight() * InteractCollisionHalfHeightMultiplier
	);

	// Attach player interact collision to player pawn, snapping to its transform
	PlayerInteractCollisionActor->AttachToComponent(PlayerMovementCollision, FAttachmentTransformRules::SnapToTargetIncludingScale);
}

void UPlayerInteractComponent::OnInteractInput()
{
	if (OverlappedInteractables.IsEmpty())
	{
		return;
	}

	// TODO: Handle multiple overlapping interactables. Use overlap begin/end delegates in interact screen widget to control showing the switch interact target widget
	IInteractable::Execute_OnInteractedWith(OverlappedInteractables[0], InteractingPawn.Get());
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
		// Remove the interactable from player interactable overlapped list
		OverlappedInteractables.Remove(OtherActor);

		// Notify interactable it has left player interact collision
		IInteractable::Execute_OnPlayerInteractEndOverlap(OtherActor);

		// Call subscribed events for when an interactable has left player interact collision
		OnEndInteractableOverlapDelegate.Broadcast(OtherActor, OverlappedInteractables.Num());
	}
}
