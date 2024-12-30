// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/StreamableManager.h"
#include "Project1GameInstanceBase.generated.h"

class UInputKeyStateController;

/**
 * 
 */
UCLASS()
class PROJECT1_API UProject1GameInstanceBase : public UGameInstance
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	TObjectPtr<UInputKeyStateController> InputKeyStateController{nullptr};

	FStreamableManager StreamableManager{};

public:
	UProject1GameInstanceBase();

	UInputKeyStateController& GetInputKeyStateController() const;

	FORCEINLINE FStreamableManager& GetStreamableManager() { return StreamableManager; }
};
