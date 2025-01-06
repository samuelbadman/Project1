// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerControllers/Project1PlayerControllerBase.h"
#include "GamePlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

/**
 *
 */
UCLASS()
class PROJECT1_API AGamePlayerController : public AProject1PlayerControllerBase
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputMappingContext> MainInputMappingContext{ nullptr };

	UPROPERTY(EditDefaultsOnly)
	int32 MainInputMappingContextPriority{ 0 };

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> TestInputAction{ nullptr };

private:
	void SetupInputComponent() override;
	void BeginPlay() override;

	void OnTestInputActionTriggered(const FInputActionValue& Value);
};
