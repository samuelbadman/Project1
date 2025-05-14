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

	const TObjectPtr<UGameUserSettings> Settings{ UGameUserSettings::GetGameUserSettings() };
	Settings->SetVSyncEnabled(true);
	Settings->ApplySettings(true);
}

USaveManager* UProject1GameInstanceBase::GetSaveManager() const
{
	return SaveManager.Get();
}
