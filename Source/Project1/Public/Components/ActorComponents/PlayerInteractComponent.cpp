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

	// TODO: Handle multiple overlapping interactables
	Cast<IInteractable>(OverlappedInteractables[0])->Execute_OnInteractedWith(OverlappedInteractables[0], InteractingPawn.Get());
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
		OverlappedInteractables.Add(OtherActor);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, FString::Printf(TEXT("Pawn capsule overlap begin [%s] [%s]"), *AActor::GetDebugName(OtherActor),
			*Cast<IInteractable>(OtherActor)->Execute_GetInteractablePromptText(OtherActor).ToString()));
	}
}

void UPlayerInteractComponent::OnPawnCollisionEndOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	OverlappedInteractables.Remove(OtherActor);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, FString::Printf(TEXT("Pawn capsule overlap end [%s]"), *AActor::GetDebugName(OtherActor)));
}
