// Fill out your copyright notice in the Description page of Project Settings.


#include "GameGameMode.h"
#include "Objects/Dialogue/DialogueManagerBase.h"

AGameGameMode::AGameGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGameGameMode::StartPlay()
{
	// Create dialogue manager instance before beginning play on actors to ensure that dialogue manager instance is valid during actor begin play
	CreateDialogueManager();

	// Parent calls begin play on actors
	Super::StartPlay();
}

void AGameGameMode::BeginPlay()
{
	Super::BeginPlay();
	DialogueManagerInstance->BeginPlay();
}

void AGameGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	DialogueManagerInstance->Tick(DeltaSeconds);
}

void AGameGameMode::CreateDialogueManager()
{
	const TSubclassOf<UDialogueManagerBase> DialogueManagerLoadedClass{ DialogueManagerClass.LoadSynchronous() };
	if (IsValid(DialogueManagerLoadedClass))
	{
		DialogueManagerInstance = NewObject<UDialogueManagerBase>(this, DialogueManagerLoadedClass);
	}
}
