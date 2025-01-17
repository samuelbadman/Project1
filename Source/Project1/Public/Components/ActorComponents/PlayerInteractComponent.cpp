// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInteractComponent.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Interfaces/Interactable.h"
#include "Kismet/KismetSystemLibrary.h"

void UPlayerInteractComponent::SetupNewPawn(TObjectPtr<APawn> Pawn)
{
	// Get pawn as character
	TObjectPtr<ACharacter> Character{ CastChecked<ACharacter>(Pawn) };

	// Get root collision shape component from character
	TObjectPtr<UCapsuleComponent> CollisionShape{ Character->GetCapsuleComponent() };

	// Bind to shape component overlap events
	CollisionShape->OnComponentBeginOverlap.AddDynamic(this, &UPlayerInteractComponent::OnPawnCollisionBeginOverlap);
	CollisionShape->OnComponentEndOverlap.AddDynamic(this, &UPlayerInteractComponent::OnPawnCollisionEndOverlap);
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
