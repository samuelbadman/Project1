// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/Project1ObjectBase.h"
#include "SaveManager.generated.h"

class USaveGame;
class UProject1SaveGame;

/**
 * 
 */
UCLASS()
class USaveManager : public UProject1ObjectBase
{
	GENERATED_BODY()
	
private:
	static constexpr int32 UserIndex{ 0 };

	UPROPERTY()
	TObjectPtr<UProject1SaveGame> SaveGameObject;

public:
	USaveManager();

	UFUNCTION(BlueprintCallable, Category = "SaveManager")
	void CreateNewSaveGame();

	UFUNCTION(BlueprintCallable, Category = "SaveManager")
	void SaveGame(const FString& SaveSlotName, const bool Async);

	UFUNCTION(BlueprintCallable, Category = "SaveManager")
	void LoadGame(const FString& SaveSlotName, const bool Async);

	UFUNCTION(BlueprintCallable, Category = "SaveManager")
	FORCEINLINE UProject1SaveGame* GetSaveGameObject() const { return SaveGameObject; }

	void ApplyLoadedGameData();

private:
	void OnGameSaved(const FString& SaveSlotName, const int32 SaveUserIndex, bool SaveSuccess);
	void OnGameLoaded(const FString& SaveSlotName, const int32 SaveUserIndex, USaveGame* LoadedSaveGame);

	void WriteSaveGameData();
};
