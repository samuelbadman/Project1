// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class PlayTime
{
private:
	uint64 Hours;
	uint8 Minutes;
	uint8 Seconds;

public:
	PlayTime();
	PlayTime(const uint64 InHours, const uint8 InMinutes, const uint8 InSeconds);
	virtual ~PlayTime();

	// Increments the play time by a second
	void IncrementSecond();

	void SetTime(const uint64 NewHours, const uint8 NewMinutes, const uint8 NewSeconds);
	FString ToString() const;
};
