// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveManager.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGame/Project1SaveGame.h"
#include "GameModes/GameGameMode.h"
#include "EngineUtils.h"

const FString USaveManager::SaveSlot1Name = TEXT("SaveSlot1");

USaveManager::USaveManager()
	: SaveGameObject(nullptr)
{
}

void USaveManager::CreateNewSaveGame()
{
	SaveGameObject = CastChecked<UProject1SaveGame>(UGameplayStatics::CreateSaveGameObject(UProject1SaveGame::StaticClass()));
	UE_LOG(LogTemp, Warning, TEXT("Created new save game."));
}

void USaveManager::SaveGame(const FString& SaveSlotName, const bool Async)
{
	// Check the save game object is valid. Cannot save the game without a valid save game object
	if (!IsValid(SaveGameObject))
	{
		UE_LOG(LogTemp, Error, TEXT("Attempting to save game with invalid save game object. Aborted."));
		return;
	}

	// Write save game data
	WriteSaveGameData();

	// Write data to disk
	if (Async)
	{
		FAsyncSaveGameToSlotDelegate AsyncDelegate{};
		AsyncDelegate.BindUObject(this, &USaveManager::OnGameSaved);
		UGameplayStatics::AsyncSaveGameToSlot(SaveGameObject, SaveSlotName, UserIndex, AsyncDelegate);
	}
	else
	{
		const bool Success{ UGameplayStatics::SaveGameToSlot(SaveGameObject, SaveSlotName, UserIndex) };
		OnGameSaved(SaveSlotName, UserIndex, Success);
	}
}

void USaveManager::LoadGame(const FString& SaveSlotName, const bool Async)
{
	if (Async)
	{
		FAsyncLoadGameFromSlotDelegate AsyncDelegate{};
		AsyncDelegate.BindUObject(this, &USaveManager::OnGameLoaded);
		UGameplayStatics::AsyncLoadGameFromSlot(SaveSlotName, UserIndex, AsyncDelegate);
	}
	else
	{
		const TObjectPtr<USaveGame> LoadedSave{ UGameplayStatics::LoadGameFromSlot(SaveSlotName, UserIndex) };
		OnGameLoaded(SaveSlotName, UserIndex, LoadedSave);
	}
}

const FString& USaveManager::GetSaveSlot1Name() const
{
	return SaveSlot1Name;
}

void USaveManager::ApplyLoadedGameData()
{
	// Apply loaded data to all actors in the world
	for (FActorIterator It(GetWorld()); It; ++It)
	{
		// Get actor referenced by iterator
		const TObjectPtr<AActor> Actor{ *It };

		// Only care about actors marked as savable
		if (!Actor->Implements<USavableObjectInterface>())
		{
			continue;
		}

		ISavableObjectInterface::Execute_Load(Actor);
	}
}

bool USaveManager::IsAnySaveDataPresent() const
{
	return UGameplayStatics::DoesSaveGameExist(SaveSlot1Name, UserIndex);
}

void USaveManager::OnGameSaved(const FString& SaveSlotName, const int32 SaveUserIndex, bool SaveSuccess)
{
	UE_LOG(LogTemp, Warning, TEXT("Saved game."));
}

void USaveManager::OnGameLoaded(const FString& SaveSlotName, const int32 SaveUserIndex, USaveGame* LoadedSaveGame)
{
	if (IsValid(LoadedSaveGame))
	{
		UE_LOG(LogTemp, Warning, TEXT("Loaded game."));

		// Retrieve loaded save game object
		SaveGameObject = CastChecked<UProject1SaveGame>(LoadedSaveGame);

		// Open saved level name
		UGameplayStatics::OpenLevel(this, SaveGameObject->LevelName);
	}
}

void USaveManager::WriteSaveGameData()
{
	// Save the name of the currently open level
	SaveGameObject->LevelName = FName(UGameplayStatics::GetCurrentLevelName(this));

	// Save all actors in the world
	for (FActorIterator It(GetWorld()); It; ++It)
	{
		// Get actor referenced by iterator
		const TObjectPtr<AActor> Actor{ *It };

		// Only care about actors marked as savable
		if (!Actor->Implements<USavableObjectInterface>())
		{
			continue;
		}

		ISavableObjectInterface::Execute_Save(Actor);
	}
}
