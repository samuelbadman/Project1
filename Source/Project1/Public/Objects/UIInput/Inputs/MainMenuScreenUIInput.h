// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/UIInput/Inputs/UIInputBase.h"
#include "MainMenuScreenUIInput.generated.h"

struct FInputActionValue;
class UInputAction;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnConfirmTriggeredDelegate, const FInputActionValue& /* Value */);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnNavigateTriggeredDelegate, const FInputActionValue& /* Value */);

/**
 * 
 */
UCLASS()
class UMainMenuScreenUIInput : public UUIInputBase
{
	GENERATED_BODY()
	
public:
	FOnConfirmTriggeredDelegate ConfirmTriggered{};
	FOnNavigateTriggeredDelegate NavigateTriggered{};

private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> ConfirmInputAction{ nullptr };

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> NavigateInputAction{ nullptr };

private:
	void SetupInput(TObjectPtr<UEnhancedInputComponent> InputComponent) override;

	void OnConfirmTriggered(const FInputActionValue& Value);
	void OnNavigateTriggered(const FInputActionValue& Value);
};
