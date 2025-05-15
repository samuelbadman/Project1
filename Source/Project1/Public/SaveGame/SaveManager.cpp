// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveManager.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGame/SaveGameObjects/MetaSaveGame.h"
#include "SaveGame/SaveGameObjects/Project1SaveGame.h"
#include "GameModes/GameGameMode.h"
#include "EngineUtils.h"

const FString USaveManager::MetaSaveSlotName = TEXT("Meta");
const FString USaveManager::SaveSlot1Name = TEXT("SaveSlot1");

USaveManager::USaveManager()
	: MetaSaveGameObject(nullptr),
	GameSaveGameObject(nullptr)
{
}

void USaveManager::CreateNewGameSaveGame()
{
	GameSaveGameObject = CastChecked<UProject1SaveGame>(UGameplayStatics::CreateSaveGameObject(UProject1SaveGame::StaticClass()));
	UE_LOG(LogTemp, Warning, TEXT("Created new game save game."));
}

void USaveManager::SaveGame(const FString& SaveSlotName, const bool Async)
{
	// Check the save game object is valid. Cannot save the game without a valid save game object
	if (!IsValid(GameSaveGameObject))
	{
		UE_LOG(LogTemp, Error, TEXT("Attempting to save game with invalid save game object. Aborted."));
		return;
	}

	// Write save game data
	WriteMetaSaveGameData(SaveSlotName);
	WriteGameSaveGameData();

	// Write data to disk
	if (Async)
	{
		FAsyncSaveGameToSlotDelegate MetaAsyncDelegate{};
		MetaAsyncDelegate.BindUObject(this, &USaveManager::OnGameSaved);
		UGameplayStatics::AsyncSaveGameToSlot(MetaSaveGameObject, MetaSaveSlotName, UserIndex, MetaAsyncDelegate);

		FAsyncSaveGameToSlotDelegate GameAsyncDelegate{};
		GameAsyncDelegate.BindUObject(this, &USaveManager::OnGameSaved);
		UGameplayStatics::AsyncSaveGameToSlot(GameSaveGameObject, SaveSlotName, UserIndex, GameAsyncDelegate);
	}
	else
	{
		OnMetaSaved(MetaSaveSlotName, UserIndex, UGameplayStatics::SaveGameToSlot(MetaSaveGameObject, MetaSaveSlotName, UserIndex));
		OnGameSaved(SaveSlotName, UserIndex, UGameplayStatics::SaveGameToSlot(GameSaveGameObject, SaveSlotName, UserIndex));
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

bool USaveManager::IsAnyGameSaveDataPresent() const
{
	return UGameplayStatics::DoesSaveGameExist(SaveSlot1Name, UserIndex);
}

void USaveManager::CreateNewMetaSaveGame()
{
	MetaSaveGameObject = CastChecked<UMetaSaveGame>(UGameplayStatics::CreateSaveGameObject(UMetaSaveGame::StaticClass()));

	UE_LOG(LogTemp, Warning, TEXT("Created meta save game."));
}

bool USaveManager::IsMetaSaveDataPresent() const
{
	return UGameplayStatics::DoesSaveGameExist(MetaSaveSlotName, UserIndex);
}

void USaveManager::LoadMetaData(bool Async)
{
	if (Async)
	{
		FAsyncLoadGameFromSlotDelegate AsyncDelegate{};
		AsyncDelegate.BindUObject(this, &USaveManager::OnMetaLoaded);
		UGameplayStatics::AsyncLoadGameFromSlot(MetaSaveSlotName, UserIndex, AsyncDelegate);
	}
	else
	{
		const TObjectPtr<USaveGame> LoadedSave{ UGameplayStatics::LoadGameFromSlot(MetaSaveSlotName, UserIndex) };
		OnMetaLoaded(MetaSaveSlotName, UserIndex, LoadedSave);
	}
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
		GameSaveGameObject = CastChecked<UProject1SaveGame>(LoadedSaveGame);

		// Open saved level name
		UGameplayStatics::OpenLevel(this, GameSaveGameObject->LevelName);
	}
}

void USaveManager::OnMetaSaved(const FString& SaveSlotName, const int32 SaveUserIndex, bool SaveSuccess)
{
	UE_LOG(LogTemp, Warning, TEXT("Saved meta save game."));
}

void USaveManager::OnMetaLoaded(const FString& SaveSlotName, const int32 SaveUserIndex, USaveGame* LoadedSaveGame)
{
	if (IsValid(LoadedSaveGame))
	{
		UE_LOG(LogTemp, Warning, TEXT("Loaded meta save game."));

		// Retrieve loaded save game object
		MetaSaveGameObject = CastChecked<UMetaSaveGame>(LoadedSaveGame);
	}
}

void USaveManager::WriteMetaSaveGameData(const FString& SaveSlotName)
{
	MetaSaveGameObject->LastGameSaveSlotNameUsed = FName(SaveSlotName);
}

void USaveManager::WriteGameSaveGameData()
{
	// Save the name of the currently open level
	GameSaveGameObject->LevelName = FName(UGameplayStatics::GetCurrentLevelName(this));

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
