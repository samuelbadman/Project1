// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayTime.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FPlayTime
{
	GENERATED_BODY()

private:
	// Marked as UPROPERTY as the FPlayTime struct is used in a save game object to save to disk in a save game slot
	UPROPERTY()
	uint64 Hours;

	// Marked as UPROPERTY as the FPlayTime struct is used in a save game object to save to disk in a save game slot
	UPROPERTY()
	uint8 Minutes;

	// Marked as UPROPERTY as the FPlayTime struct is used in a save game object to save to disk in a save game slot
	UPROPERTY()
	uint8 Seconds;

public:
	FPlayTime();
	FPlayTime(const uint64 InHours, const uint8 InMinutes, const uint8 InSeconds);

	// Increments the play time by a second
	void IncrementSecond();

	void SetTime(const uint64 NewHours, const uint8 NewMinutes, const uint8 NewSeconds);
	FString ToString() const;
};
