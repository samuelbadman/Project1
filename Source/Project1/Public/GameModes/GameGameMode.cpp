// Fill out your copyright notice in the Description page of Project Settings.


#include "GameGameMode.h"
#include "Objects/Dialogue/DialogueManagerBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameInstances/Project1GameInstanceBase.h"
#include "SaveGame/SaveDataStructures/GameModeSaveData.h"
#include "SaveGame/SaveManager.h"
#include "SaveGame/SaveGameObjects/Project1SaveGame.h"

AGameGameMode::AGameGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bTickEvenWhenPaused = true;
}

void AGameGameMode::SetTotalPlayTime(const FPlayTime& InTotalPlayTime)
{
	TotalPlayTime = InTotalPlayTime;
}

void AGameGameMode::Save_Implementation()
{
	const TObjectPtr<USaveManager> SaveManager{ CastChecked<UProject1GameInstanceBase>(UGameplayStatics::GetGameInstance(this))->GetSaveManager() };
	const TObjectPtr<UProject1SaveGame> SaveGame{ SaveManager->GetGameSaveGameObject() };

	FGameModeSaveData SaveData{};
	SaveData.TotalPlayTime = TotalPlayTime;

	SaveGame->GameModeSaveData = SaveData;
}

void AGameGameMode::Load_Implementation()
{
	const TObjectPtr<USaveManager> SaveManager{ CastChecked<UProject1GameInstanceBase>(UGameplayStatics::GetGameInstance(this))->GetSaveManager() };
	const TObjectPtr<UProject1SaveGame> SaveGame{ SaveManager->GetGameSaveGameObject() };

	TotalPlayTime = SaveGame->GameModeSaveData.TotalPlayTime;
	OnTotalPlayTimeChanged.Broadcast(TotalPlayTime);
}

void AGameGameMode::StartPlay()
{
	// Create dialogue manager instance before beginning play on actors to ensure that dialogue manager instance is valid during actor begin play
	CreateDialogueManager();

	// Apply loaded game data to game state
	const TObjectPtr<USaveManager> SaveManager{ CastChecked<UProject1GameInstanceBase>(UGameplayStatics::GetGameInstance(this))->GetSaveManager() };
	SaveManager->ApplyLoadedGameData();

	// Parent call calls begin play on actors
	Super::StartPlay();
}

void AGameGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Begin dialogue manager instance
	DialogueManagerInstance->BeginPlay();
}

void AGameGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	const bool GamePaused{ UGameplayStatics::IsGamePaused(this) };

	// Update second counter
	ElapsedDeltaSeconds += DeltaSeconds;
	if (ElapsedDeltaSeconds >= 1.0f)
	{
		OnSecondElapsed(GamePaused);
		ElapsedDeltaSeconds = 0.0f;
	}

	// This actor is set to still tick when the game is paused. This is to continue timing the total time played while the game is paused as timers get paused by pausing the game
	// Functionality of this actor that should not run when the game is paused should be put into the else branch of this if
	if (GamePaused)
	{
		TickPaused(DeltaSeconds);
	}
	else
	{
		TickUnpaused(DeltaSeconds);
	}
}

void AGameGameMode::TickPaused(float DeltaSeconds)
{
}

void AGameGameMode::TickUnpaused(float DeltaSeconds)
{
	DialogueManagerInstance->Tick(DeltaSeconds);
}

void AGameGameMode::OnSecondElapsed(bool GamePaused)
{
	// Update total time game played
	TotalPlayTime.IncrementSecond();
	OnTotalPlayTimeChanged.Broadcast(TotalPlayTime);

	OnGameSecondElapsed.Broadcast(GamePaused);
}

void AGameGameMode::CreateDialogueManager()
{
	const TSubclassOf<UDialogueManagerBase> DialogueManagerLoadedClass{ DialogueManagerClass.LoadSynchronous() };

	if (IsValid(DialogueManagerLoadedClass))
	{
		DialogueManagerInstance = NewObject<UDialogueManagerBase>(this, DialogueManagerLoadedClass);
	}
}
