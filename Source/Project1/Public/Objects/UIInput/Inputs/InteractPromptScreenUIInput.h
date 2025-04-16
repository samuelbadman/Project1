// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/UIInput/Inputs/UIInputBase.h"
#include "InteractPromptScreenUIInput.generated.h"

struct FInputActionValue;
class UInputAction;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnInteractTriggeredDelegate, const FInputActionValue& /* Value */);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnSwitchActionTriggeredDelegate, const FInputActionValue& /* Value */);

/**
 * 
 */
UCLASS()
class UInteractPromptScreenUIInput : public UUIInputBase
{
	GENERATED_BODY()
	
public:
	FOnInteractTriggeredDelegate InteractTriggered{};
	FOnSwitchActionTriggeredDelegate SwitchActionTriggered{};

private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputMappingContext> InputMappingContext{ nullptr };

	UPROPERTY(EditDefaultsOnly)
	int32 InputPriority{ 10 };

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> InteractInputAction{ nullptr };

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> SwitchActionInputAction{ nullptr };

private:
	void SetupInput(TObjectPtr<UEnhancedInputComponent> InputComponent) override;
	TObjectPtr<UInputMappingContext> GetInputMappingContext() const override;
	int32 GetInputPriority() const override;

	void OnInteractTriggered(const FInputActionValue& Value);
	void OnSwitchActionTriggered(const FInputActionValue& Value);
};
