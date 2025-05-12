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
	~PlayTime();

	void AddSecond();
	FString ToString() const;
};
