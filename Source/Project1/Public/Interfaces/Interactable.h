// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

struct FInteractableDescription;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECT1_API IInteractable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, Category = "Interactable")
	void GetInteractableDescription(FInteractableDescription& OutInteractableDescription);

	//UFUNCTION(BlueprintNativeEvent, Category = "Interactable")
	//FText GetInteractActionText();

	//UFUNCTION(BlueprintNativeEvent, Category = "Interactable")
	//bool IsLongPressInteract();

	//UFUNCTION(BlueprintNativeEvent, Category = "Interactable")
	//float GetLongPressInteractDuration();

	UFUNCTION(BlueprintNativeEvent, Category = "Interactable")
	void OnPlayerInteractBeginOverlap();

	UFUNCTION(BlueprintNativeEvent, Category = "Interactable")
	void OnPlayerInteractEndOverlap();

	UFUNCTION(BlueprintNativeEvent, Category = "Interactable")
	void OnInteractedWith(AActor* Interactor);

	// Called when a hold interact is started
	UFUNCTION(BlueprintNativeEvent, Category = "Interactable")
	void OnHoldInteractStarted(AActor* Interactor);

	// Called each frame the hold interact is updated/progressed/ticked
	UFUNCTION(BlueprintNativeEvent, Category = "Interactable")
	void OnHoldInteractTicked(AActor* Interactor, float DeltaTime, float PercentComplete);

	// Called when the hold interact is completed.
	// NOTE: This event is here in case an interactable wants to handle specifically completing a hold interact. The OnInteractedWith event will be called when a hold
	// interact is completed as well as this event
	UFUNCTION(BlueprintNativeEvent, Category = "Interactable")
	void OnHoldInteractCompleted(AActor* Interactor);

	// Called when the interactor stops the hold interaction without completing the interaction
	UFUNCTION(BlueprintNativeEvent, Category = "Interactable")
	void OnHoldInteractCanceled(AActor* Interactor, float PercentComplete);
};
