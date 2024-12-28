// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Project1PlayerControllerBase.generated.h"

class UProject1GameInstanceBase;

/**
 * 
 */
UCLASS()
class PROJECT1_API AProject1PlayerControllerBase : public APlayerController
{
	GENERATED_BODY()
	
private:
	TObjectPtr<UProject1GameInstanceBase> ProjectGameInstance{ nullptr };

private:
	void SetupInputComponent() override;
	void BeginPlay() override;

	void OnAnyKeyInput(const FKey& Key, const EInputEvent InputEvent);
};
