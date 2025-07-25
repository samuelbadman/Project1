// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveManager.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "SaveGame/SaveGameObjects/MetaSaveGame.h"
#include "SaveGame/SaveGameObjects/Project1SaveGame.h"
#include "GameModes/GameGameMode.h"
#include "EngineUtils.h"

const FString USaveManager::MetaSaveSlotName = TEXT("Meta");
const FString USaveManager::GameSaveSlotName = TEXT("GameSave");

USaveManager::USaveManager()
	: MetaSaveGameObject(nullptr),
	GameSaveGameObject(nullptr),
	AvailableSaveSlotIds({}),
	SaveSlots({})
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

	// Update save slot data that stores information about the save
	// Get the slot data that was saved into
	FSaveSlot* const SlotDataSavedTo{ GetExistingSaveSlotFromName(SaveSlotName) };

	// Update saved time and date info for slot saved into
	// Get current local time on this machine
	const FDateTime Now{ UKismetMathLibrary::Now() };

	UpdateTimeDateSavedDataForSlot(*SlotDataSavedTo, Now);

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
	return !SaveSlots.IsEmpty();

	//for (int32 Id : UsedSaveSlotIds)
	//{
	//	if (UGameplayStatics::DoesSaveGameExist(ConstructSaveSlotName(Id).ToString(), UserIndex))
	//	{
	//		return true;
	//	}
	//}
	//return false;
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

bool USaveManager::LoadMetaData(bool Async)
{
	if (!UGameplayStatics::DoesSaveGameExist(MetaSaveSlotName, UserIndex))
	{
		return false;
	}

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

	return true;
}

int32 USaveManager::CreateNewSaveSlot()
{
	// Get new unique save slot id
	const int32 NewSlotId{ TakeAvailableSaveSlotId() };

	// Create new save slot data and add it to the save slot map
	SaveSlots.Emplace(NewSlotId, FSaveSlot
		{
			.Id = NewSlotId,
			.UniqueName = ConstructSaveSlotName(NewSlotId)
		}
	);

	// Return the id of the new save slot used to reference the save slot from client code
	return NewSlotId;
}

const FSaveSlot* USaveManager::GetSaveSlotData(const int32 Id) const
{
	return SaveSlots.Find(Id);
}

void USaveManager::OnGameSaved(const FString& SaveSlotName, const int32 SaveUserIndex, bool SaveSuccess)
{
	UE_LOG(LogTemp, Warning, TEXT("Saved game."));

	// TODO: Notify slot data has changed, such as time date saved

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

		// Retrieve loaded meta save game object
		MetaSaveGameObject = CastChecked<UMetaSaveGame>(LoadedSaveGame);

		// Clear existing save slot data if there is any
		if (!SaveSlots.IsEmpty())
		{
			SaveSlots.Empty();
		}

		// Update available and used save game ids
		InitializeSaveSlotIds();

		// For each saved slot in the meta save game data, create new save slot data in the save manager
		const TArray<FSaveSlotSaveData>& LoadedSaveSlots{ MetaSaveGameObject->GameSaveSlots };
		for (const FSaveSlotSaveData& SlotData : LoadedSaveSlots)
		{
			AvailableSaveSlotIds.Remove(SlotData.Id);
			SaveSlots.Emplace(SlotData.Id, FSaveSlot
				{
					.Id = SlotData.Id, 
					.UniqueName = SlotData.UniqueSlotName, 
					.TimeDateSaved = SlotData.TimeDateSaved
				});
		}
	}
}

void USaveManager::WriteMetaSaveGameData(const FString& SaveSlotName)
{
	// Save created save slot info
	const int32 NumSaveSlots{ SaveSlots.Num() };
	MetaSaveGameObject->GameSaveSlots.Empty(NumSaveSlots);

	// This needs to be for each save slot id key in the map
	// For each slot we are adding a new slot to game save slots which is persistent. 
	// NOTE: Iterating over a map here
	for (const TPair<int32, FSaveSlot>& Slot : SaveSlots)
	{
		MetaSaveGameObject->GameSaveSlots.Emplace(FSaveSlotSaveData
			{
				.Id = Slot.Key,
				.UniqueSlotName = ConstructSaveSlotName(Slot.Key),
				.TimeDateSaved = Slot.Value.TimeDateSaved
			});
	}

	// Save last used game save slot name
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

void USaveManager::InitializeSaveSlotIds()
{
	AvailableSaveSlotIds.SetNumUninitialized(MaximumSaveSlotCount, EAllowShrinking::Yes);
	SaveSlots.Empty();

	for (int32 i = 0; i < MaximumSaveSlotCount; ++i)
	{
		AvailableSaveSlotIds[i] = i;
	}
}

int32 USaveManager::TakeAvailableSaveSlotId()
{
	const int32 Id{ AvailableSaveSlotIds.Last() };
	AvailableSaveSlotIds.Remove(Id);
	return Id;
}

FName USaveManager::ConstructSaveSlotName(const int32 Id) const
{
	FString Name{ GameSaveSlotName };
	Name.AppendInt(Id);
	return FName(Name);
}

FSaveSlot* USaveManager::GetExistingSaveSlotFromName(const FString& SaveSlotName)
{
	// Find the save slot data structure with the supplied save slot name
	// NOTE: Iterating over map
	for (const TPair<int32, FSaveSlot>& Slot : SaveSlots)
	{
		if (Slot.Value.UniqueName.ToString() == SaveSlotName)
		{
			return SaveSlots.Find(Slot.Key);
		}
	}

	// No save slot exists with the supplied save slot name
	return nullptr;
}

void USaveManager::UpdateTimeDateSavedDataForSlot(FSaveSlot& SaveSlotData, const FDateTime& Now)
{
	// Build date time string in required format
	FStringBuilderBase DateTimeStringBuilder{};
	Now.ToString(TEXT("%d/%m/%Y-%H:%M:%S"), DateTimeStringBuilder);

	// Update data struct
	SaveSlotData.TimeDateSaved = FName(DateTimeStringBuilder.ToString());
}
