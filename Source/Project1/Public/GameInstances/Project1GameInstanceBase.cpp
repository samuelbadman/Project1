// Fill out your copyright notice in the Description page of Project Settings.


#include "Project1GameInstanceBase.h"
#include "GameFramework/GameUserSettings.h"

void UProject1GameInstanceBase::Init()
{
	Super::Init();
	const TObjectPtr<UGameUserSettings> Settings{ UGameUserSettings::GetGameUserSettings() };
	Settings->SetVSyncEnabled(true);
	Settings->ApplySettings(true);
}
