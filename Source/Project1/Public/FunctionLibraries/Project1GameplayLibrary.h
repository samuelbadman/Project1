// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Project1GameplayLibrary.generated.h"

class UInteractionBase;
enum class EInteractionType : uint8;

/**
 * 
 */
UCLASS()
class PROJECT1_API UProject1GameplayLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	// Returns true if the in actor is the player character actor
	UFUNCTION(BlueprintCallable, Category = "Project1GameplayLibrary")
	static bool IsActorPlayerCharacter(UObject* WorldContextObject, AActor* Actor);

	// Returns a newly constructed interaction object using NewObject() for the interaction type. Can return null if the interaction type is not implemented or NewObject() fails
	UFUNCTION(BlueprintCallable, Category = "Project1GameplayLibrary")
	static UInteractionBase* CreateInteraction(EInteractionType InteractionType, UObject* Outer);
};
