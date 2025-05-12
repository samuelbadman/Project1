// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameModes/Project1GameModeBase.h"
#include "Classes/PlayTime.h"
#include "GameGameMode.generated.h"

class UDialogueManagerBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameSecondElapsedSignature, bool, GamePaused);

/**
 * 
 */
UCLASS()
class PROJECT1_API AGameGameMode : public AProject1GameModeBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable)
	FOnGameSecondElapsedSignature OnGameSecondElapsed{};

private:
	UPROPERTY(EditDefaultsOnly, Category = "Dialogue")
	TSoftClassPtr<UDialogueManagerBase> DialogueManagerClass{ nullptr };

	// Level dialogue manager instance
	UPROPERTY()
	TObjectPtr<UDialogueManagerBase> DialogueManagerInstance{ nullptr };

	float ElapsedDeltaSeconds{ 0.0f };

	// Total play time
	PlayTime TotalPlayTime{};

public:
	AGameGameMode();

	FORCEINLINE UDialogueManagerBase* GetDialogueManager() const { return DialogueManagerInstance; }
	FORCEINLINE const PlayTime& GetTotalPlayTime() const { return TotalPlayTime; }

private:
	void StartPlay() override;
	void BeginPlay() override;
	void Tick(float DeltaSeconds) override;

	void TickPaused(float DeltaSeconds);
	void TickUnpaused(float DeltaSeconds);

	void OnSecondElapsed(bool GamePaused);

	void CreateDialogueManager();
};
