// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/Project1ObjectBase.h"
#include "SaveManager.generated.h"

class USaveGame;
class UProject1SaveGame;
class UMetaSaveGame;

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

	TArray<int32> AvailableSaveSlotIds;
	TArray<int32> UsedSaveSlotIds;

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

	UFUNCTION(BlueprintCallable, Category = "SaveManager")
	FName GetNewUniqueSaveSlotName();

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
	FName ConstructSaveSlotName(const int32 Id) const;
};
