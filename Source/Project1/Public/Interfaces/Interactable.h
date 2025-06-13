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
	void OnPlayerInteractBeginOverlap();

	UFUNCTION(BlueprintNativeEvent, Category = "Interactable")
	void OnPlayerInteractEndOverlap();

	UFUNCTION(BlueprintNativeEvent, Category = "Interactable")
	void OnBecomeTargetedInteractable(AActor* Interactor);

	UFUNCTION(BlueprintNativeEvent, Category = "Interactable")
	void GetInteractableDescription(FInteractableDescription& OutDescription);

	UFUNCTION(BlueprintNativeEvent, Category = "Interactable")
	void OnInteractedWith(AActor* Interactor);

	UFUNCTION(BlueprintNativeEvent, Category = "Interactable")
	void OnInteractionStarted(AActor* Interactor);

	UFUNCTION(BlueprintNativeEvent, Category = "Interactable")
	void OnInteractionCompleted(AActor* Interactor);

	UFUNCTION(BlueprintNativeEvent, Category = "Interactable")
	void OnInteractionCanceled(AActor* Interactor, float CompletionPercent);

	UFUNCTION(BlueprintNativeEvent, Category = "Interactable")
	void OnInteractionCompletionPercentChanged(AActor* Interactor, float CompletionPercent);
};
