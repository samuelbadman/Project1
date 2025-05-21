// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveGame/SaveDataStructures/SaveSlotSaveData.h"
#include "MetaSaveGame.generated.h"

/**
 * Meta save game data is created every time the game is saved by the player into any project 1 save slot. Only one meta save game file exists on disk
 */
UCLASS()
class UMetaSaveGame : public USaveGame
{
	GENERATED_BODY()
	
	// NOTE: All variables (including those inside structures!) being saved/loaded in the save game object MUST be marked UPROPERTY()

public:
	UPROPERTY(BlueprintReadWrite, Category = "MetaSaveGame")
	FName LastGameSaveSlotNameUsed{ NAME_None };

	UPROPERTY(BlueprintReadWrite, Category = "MetaSaveGame")
	TArray<FSaveSlotSaveData> GameSaveSlots{};
};
