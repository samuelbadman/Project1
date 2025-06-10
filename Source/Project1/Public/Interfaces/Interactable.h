// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

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
	FText GetInteractActionText();

	UFUNCTION(BlueprintNativeEvent, Category = "Interactable")
	bool IsLongPressInteract();

	UFUNCTION(BlueprintNativeEvent, Category = "Interactable")
	float GetLongPressInteractDuration();


	UFUNCTION(BlueprintNativeEvent, Category = "Interactable")
	void OnPlayerInteractBeginOverlap();

	UFUNCTION(BlueprintNativeEvent, Category = "Interactable")
	void OnPlayerInteractEndOverlap();

	UFUNCTION(BlueprintNativeEvent, Category = "Interactable")
	void OnInteractedWith(AActor* Interactor);


	// Called when a long press interact is started
	UFUNCTION(BlueprintNativeEvent, Category = "Interactable")
	void OnLongPressInteractStarted(AActor* Interactor);

	// Called each frame the long press interact is updated/progressed/ticked
	UFUNCTION(BlueprintNativeEvent, Category = "Interactable")
	void OnLongPressInteractTicked(AActor* Interactor, float DeltaTime, float PercentComplete);

	// Called when the long press interact is completed.
	// NOTE: This event is here in case an interactable wants to handle specifically completing a long press interact. The OnInteractedWith event will be called when a long press 
	// interact is completed as well as this event
	UFUNCTION(BlueprintNativeEvent, Category = "Interactable")
	void OnLongPressInteractCompleted(AActor* Interactor);

	// Called when the interactor stops the long press interaction without completing the interaction
	UFUNCTION(BlueprintNativeEvent, Category = "Interactable")
	void OnLongPressInteractCanceled(AActor* Interactor, float PercentComplete);
};
