// Fill out your copyright notice in the Description page of Project Settings.


#include "Project1SaveGame.h"

UProject1SaveGame::UProject1SaveGame()
	: OpenLevelName(NAME_None)
{
}

void UProject1SaveGame::SetOpenLevelName(const FName& Name)
{
	OpenLevelName = Name;
}
