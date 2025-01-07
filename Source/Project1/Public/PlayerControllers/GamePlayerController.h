// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerControllers/Project1PlayerControllerBase.h"
#include "GamePlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UPlayerCharacterControllerComponent;

/**
 *
 */
UCLASS()
class PROJECT1_API AGamePlayerController : public AProject1PlayerControllerBase
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UPlayerCharacterControllerComponent> PlayerCharacterControllerComponent{ nullptr };

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> MainInputMappingContext{ nullptr };

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	int32 MainInputMappingContextPriority{ 0 };

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> JumpInputAction{ nullptr };

public:
	AGamePlayerController();

private:
	void SetupInputComponent() override;
	void OnPossess(APawn* aPawn) override;
	void BeginPlay() override;

	void OnJumpTriggered(const FInputActionValue& Value);
};
