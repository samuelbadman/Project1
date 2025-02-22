// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Project1GameplayLibrary.generated.h"

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
	static bool IsPlayerCharacter(UObject* WorldContextObject, AActor* Actor);
};
