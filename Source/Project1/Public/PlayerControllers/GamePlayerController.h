// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerControllers/Project1PlayerControllerBase.h"
#include "GamePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT1_API AGamePlayerController : public AProject1PlayerControllerBase
{
	GENERATED_BODY()
	
private:
	void ReceiveAnyKeyInput(const FKey& Key, EInputEvent InputEvent) override;
};
