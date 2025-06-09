// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/Project1ObjectBase.h"
#include "SaveManager.generated.h"

class USaveGame;
class UProject1SaveGame;
class UMetaSaveGame;

// Callback for on slot data changed. Bound to when slot widgets are created

USTRUCT(BlueprintType)
struct FSaveSlot
{
	GENERATED_BODY()

	// NOTE: This struct is basically a copy of save slot save data structure. Could it just use that struct instead of creating a new one here?

	int32 Id{ 0 };
	FName UniqueName{ NAME_None };
	FName TimeDateSaved{ NAME_None };
};

/**
 * 
 */
UCLASS()
class USaveManager : public UProject1ObjectBase
{
	GENERATED_BODY()
	
private:
	static constexpr int32 UserIndex{ 0 };
	static constexpr int32 MaximumSaveSlotCount{ TNumericLimits<uint8>::Max() };

	static const FString MetaSaveSlotName;
	static const FString GameSaveSlotName;

	UPROPERTY()
	TObjectPtr<UMetaSaveGame> MetaSaveGameObject;

	UPROPERTY()
	TObjectPtr<UProject1SaveGame> GameSaveGameObject;

	// Array of free available Ids not in use by an existing save slot
	TArray<int32> AvailableSaveSlotIds;

	// Map Key: save slot id, Value: save slot data struct. Stores save slot data mapped to its unique id
	TMap<int32, FSaveSlot> SaveSlots;

public:
	USaveManager();

	UFUNCTION(BlueprintCallable, Category = "SaveManager")
	void CreateNewGameSaveGame();

	UFUNCTION(BlueprintCallable, Category = "SaveManager")
	void SaveGame(const FString& SaveSlotName, const bool Async);

	UFUNCTION(BlueprintCallable, Category = "SaveManager")
	void LoadGame(const FString& SaveSlotName, const bool Async);

	UFUNCTION(BlueprintCallable, Category = "SaveManager")
	FORCEINLINE UProject1SaveGame* GetGameSaveGameObject() const { return GameSaveGameObject; }

	UFUNCTION(BlueprintCallable, Category = "SaveManager")
	FORCEINLINE UMetaSaveGame* GetMetaSaveGameObject() const { return MetaSaveGameObject; }

	int32 CreateNewSaveSlot();
	// Returns a pointer to the save slot data at the id. Returned pointer is null when there is no data at the Id. The pointer is only valid until the next change of the save 
	// manager's internal save slot map's keys
	const FSaveSlot* GetSaveSlotData(const int32 Id) const;

	void ApplyLoadedGameData();
	bool IsAnyGameSaveDataPresent() const;
	void InitializeSaveSlotIds();

	void CreateNewMetaSaveGame();
	bool IsMetaSaveDataPresent() const;
	// Returns true if meta data is present and can be loaded otherwise, returns false meaning that meta data is not present on disk and could not be loaded
	bool LoadMetaData(bool Async);

private:
	void OnGameSaved(const FString& SaveSlotName, const int32 SaveUserIndex, bool SaveSuccess);
	void OnGameLoaded(const FString& SaveSlotName, const int32 SaveUserIndex, USaveGame* LoadedSaveGame);
	void OnMetaSaved(const FString& SaveSlotName, const int32 SaveUserIndex, bool SaveSuccess);
	void OnMetaLoaded(const FString& SaveSlotName, const int32 SaveUserIndex, USaveGame* LoadedSaveGame);

	void WriteMetaSaveGameData(const FString& SaveSlotName);
	void WriteGameSaveGameData();

	int32 TakeAvailableSaveSlotId();
	// TODO: void ReturnAvailableSaveSlotId(int32 Id)
	FName ConstructSaveSlotName(const int32 Id) const;
	// Returned pointer only valid until next change to save slots map
	FSaveSlot* GetExistingSaveSlotFromName(const FString& SaveSlotName);
	void UpdateTimeDateSavedDataForSlot(FSaveSlot& SaveSlotData, const FDateTime& Now);
};
