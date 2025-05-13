// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Classes/PlayTime.h"
#include "Project1SaveGame.generated.h"

/**
 * 
 */
UCLASS()
class UProject1SaveGame : public USaveGame
{
	GENERATED_BODY()
	
private:
	// NOTE: All variables being saved/loaded in the save game object MUST be marked UPROPERTY()

	UPROPERTY()
	FName OpenLevelName;

	UPROPERTY()
	FPlayTime TotalPlayTime;

public:
	UProject1SaveGame();

	void SetOpenLevelName(const FName& Name);
	FORCEINLINE const FName& GetOpenLevelName() const { return OpenLevelName; }

	void SetTotalPlayTime(const FPlayTime& InPlayTime);
	FORCEINLINE const FPlayTime& GetTotalPlayTime() const { return TotalPlayTime; }
};
