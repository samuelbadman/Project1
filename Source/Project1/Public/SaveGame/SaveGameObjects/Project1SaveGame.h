// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveGame/SaveDataStructures/GameModeSaveData.h"
#include "SaveGame/SaveDataStructures/PickupSaveData.h"
#include "Project1SaveGame.generated.h"

/**
 * 
 */
UCLASS()
class UProject1SaveGame : public USaveGame
{
	GENERATED_BODY()
	
	// NOTE: All variables (including those inside structures!) being saved/loaded in the save game object MUST be marked UPROPERTY()

public:
	UPROPERTY()
	FName LevelName{ NAME_None };

	UPROPERTY(BlueprintReadWrite, Category = "Project1SaveGame")
	FGameModeSaveData GameModeSaveData{};

	UPROPERTY(BlueprintReadWrite, Category = "Project1SaveGame")
	TMap<FName, FPickupSaveData> StaticPickupSaveData{};
};
