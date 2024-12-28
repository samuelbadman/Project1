// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Project1GameInstanceBase.generated.h"

class UInputKeyStateManager;

/**
 * 
 */
UCLASS()
class PROJECT1_API UProject1GameInstanceBase : public UGameInstance
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	TObjectPtr<UInputKeyStateManager> InputKeyStateManager{nullptr};

public:
	UProject1GameInstanceBase();

	FORCEINLINE UInputKeyStateManager& GetInputKeyStateManager() const { return *InputKeyStateManager; }
};
