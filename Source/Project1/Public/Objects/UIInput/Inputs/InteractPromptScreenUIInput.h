// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/UIInput/Inputs/UIInputBase.h"
#include "InteractPromptScreenUIInput.generated.h"

struct FInputActionValue;
class UInputAction;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnInteractStartedDelegate, const FInputActionValue& /* Value */);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnInteractTriggeredDelegate, const FInputActionValue& /* Value */);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnInteractCompletedDelegate, const FInputActionValue& /* Value */);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnSwitchActionTriggeredDelegate, const FInputActionValue& /* Value */);

/**
 * 
 */
UCLASS()
class UInteractPromptScreenUIInput : public UUIInputBase
{
	GENERATED_BODY()
	
public:
	FOnInteractStartedDelegate InteractStarted{};
	FOnInteractTriggeredDelegate InteractTriggered{};
	FOnInteractCompletedDelegate InteractCompleted{};
	FOnSwitchActionTriggeredDelegate SwitchActionTriggered{};

private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> InteractInputAction{ nullptr };

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> SwitchActionInputAction{ nullptr };

private:
	void SetupInput(TObjectPtr<UEnhancedInputComponent> InputComponent) override;

	void OnInteractStarted(const FInputActionValue& Value);
	void OnInteractTriggered(const FInputActionValue& Value);
	void OnInteractCompleted(const FInputActionValue& Value);
	void OnSwitchActionTriggered(const FInputActionValue& Value);
};
