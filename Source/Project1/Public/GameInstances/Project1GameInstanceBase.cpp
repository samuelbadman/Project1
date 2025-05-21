// Fill out your copyright notice in the Description page of Project Settings.


#include "Project1GameInstanceBase.h"
#include "GameFramework/GameUserSettings.h"
#include "SaveGame/SaveManager.h"

UProject1GameInstanceBase::UProject1GameInstanceBase()
{
	SaveManager = CreateDefaultSubobject<USaveManager>(FName(TEXT("SaveManager")));
}

void UProject1GameInstanceBase::Init()
{
	Super::Init();

	// Load meta save game data if present otherwise create a new meta save game.
	if (SaveManager->IsMetaSaveDataPresent())
	{
		// Load meta data. Save manager save slot ids are initialized on meta data loaded
		SaveManager->LoadMetaData(false);
	}
	else
	{
		// Create new meta save data. Save manger save slot ids need to be initialized
		SaveManager->CreateNewMetaSaveGame();
		SaveManager->InitializeSaveSlotIds();
	}

	// Set game user settings
	const TObjectPtr<UGameUserSettings> Settings{ UGameUserSettings::GetGameUserSettings() };
	Settings->SetVSyncEnabled(true);
	Settings->ApplySettings(true);
}

USaveManager* UProject1GameInstanceBase::GetSaveManager() const
{
	return SaveManager;
}
