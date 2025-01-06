// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/StreamableManager.h"
#include "Project1GameInstanceBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT1_API UProject1GameInstanceBase : public UGameInstance
{
	GENERATED_BODY()
	
private:
	FStreamableManager StreamableManager{};

public:
	FORCEINLINE FStreamableManager& GetStreamableManager() { return StreamableManager; }
};
