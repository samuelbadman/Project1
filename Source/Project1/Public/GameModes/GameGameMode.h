// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameModes/Project1GameModeBase.h"
#include "GameGameMode.generated.h"

class UDialogueManagerBase;

/**
 * 
 */
UCLASS()
class PROJECT1_API AGameGameMode : public AProject1GameModeBase
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Dialogue")
	TSoftClassPtr<UDialogueManagerBase> DialogueManagerClass{ nullptr };

	// Level dialogue manager instance
	UPROPERTY()
	TObjectPtr<UDialogueManagerBase> DialogueManagerInstance{ nullptr };

public:
	AGameGameMode();

	FORCEINLINE UDialogueManagerBase* GetDialogueManager() const { return DialogueManagerInstance; }

private:
	void StartPlay() override;
	void BeginPlay() override;
	void Tick(float DeltaSeconds) override;

	void CreateDialogueManager();
};
