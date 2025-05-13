// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveManager.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGame/Project1SaveGame.h"
#include "GameModes/GameGameMode.h"

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

	// Set data inside save game object
	WriteSaveGameObjectSaveData();

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
		HandleLoadedSaveGameObjectData();
	}
}

void USaveManager::WriteSaveGameObjectSaveData()
{
	// This is where the game state is saved. Gather data that needs to be saved and set in save game object. TODO: This does not have to be done all in one go. Consider
	// creating functionality to save only specific data
	SaveGameObject->SetOpenLevelName(FName(UGameplayStatics::GetCurrentLevelName(this)));
	SaveGameObject->SetTotalPlayTime(CastChecked<AGameGameMode>(UGameplayStatics::GetGameMode(this))->GetTotalPlayTime());
}

void USaveManager::HandleLoadedSaveGameObjectData()
{
	// Handle loaded save game object and update game state
	// TODO: Currently handling the loaded save game state is currently done by individual objects as this functions opens a new map which recreates most other game objects. 
	// Is this the best way to handle loaded game data?

	// Open the level
	UGameplayStatics::OpenLevel(this, SaveGameObject->GetOpenLevelName());
}
