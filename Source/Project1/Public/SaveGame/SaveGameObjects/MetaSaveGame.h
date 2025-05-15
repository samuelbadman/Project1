// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MetaSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class UMetaSaveGame : public USaveGame
{
	GENERATED_BODY()
	
	// NOTE: All variables (including those inside structures!) being saved/loaded in the save game object MUST be marked UPROPERTY()

public:
	UPROPERTY(BlueprintReadWrite, Category = "MetaSaveGame")
	FName LastGameSaveSlotNameUsed{ NAME_None };
};
