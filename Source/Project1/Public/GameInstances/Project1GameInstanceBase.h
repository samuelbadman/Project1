// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
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

public:
	UProject1GameInstanceBase();

	FORCEINLINE UInputKeyStateController& GetInputKeyStateController() const { return *InputKeyStateController; }
};
