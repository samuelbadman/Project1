// Fill out your copyright notice in the Description page of Project Settings.


#include "Project1SaveGame.h"

UProject1SaveGame::UProject1SaveGame()
	: OpenLevelName(NAME_None),
	TotalPlayTime({})
{
}

void UProject1SaveGame::SetOpenLevelName(const FName& Name)
{
	OpenLevelName = Name;
}

void UProject1SaveGame::SetTotalPlayTime(const FPlayTime& InPlayTime)
{
	TotalPlayTime = InPlayTime;
}
