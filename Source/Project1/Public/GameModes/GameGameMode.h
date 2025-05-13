// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameModes/Project1GameModeBase.h"
#include "Classes/PlayTime.h"
#include "GameGameMode.generated.h"

class UDialogueManagerBase;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameSecondElapsedSignature, bool /*GamePaused*/);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnTotalPlayTimeChangedSignature, const FPlayTime& /*NewPlayTime*/);

/**
 * 
 */
UCLASS()
class PROJECT1_API AGameGameMode : public AProject1GameModeBase
{
	GENERATED_BODY()
	
public:
	FOnGameSecondElapsedSignature OnGameSecondElapsed{};
	FOnTotalPlayTimeChangedSignature OnTotalPlayTimeChanged{};

private:
	UPROPERTY(EditDefaultsOnly, Category = "Dialogue")
	TSoftClassPtr<UDialogueManagerBase> DialogueManagerClass{ nullptr };

	// Level dialogue manager instance
	UPROPERTY()
	TObjectPtr<UDialogueManagerBase> DialogueManagerInstance{ nullptr };

	float ElapsedDeltaSeconds{ 0.0f };

	// Total play time
	FPlayTime TotalPlayTime{};

public:
	AGameGameMode();

	void SetTotalPlayTime(const FPlayTime& InTotalPlayTime);

	FORCEINLINE UDialogueManagerBase* GetDialogueManager() const { return DialogueManagerInstance; }
	FORCEINLINE const FPlayTime& GetTotalPlayTime() const { return TotalPlayTime; }

private:
	void StartPlay() override;
	void BeginPlay() override;
	void Tick(float DeltaSeconds) override;

	void TickPaused(float DeltaSeconds);
	void TickUnpaused(float DeltaSeconds);

	void OnSecondElapsed(bool GamePaused);

	void CreateDialogueManager();
};
