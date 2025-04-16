// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/UIInput/Inputs/UIInputBase.h"
#include "PressAnyInputScreenUIInput.generated.h"

struct FInputActionValue;
class UInputAction;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnAnyInputTriggeredDelegate, const FInputActionValue& /* Value */);

/**
 * 
 */
UCLASS()
class UPressAnyInputScreenUIInput : public UUIInputBase
{
	GENERATED_BODY()
	
public:
	FOnAnyInputTriggeredDelegate AnyInputTriggered{};

private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputMappingContext> PressAnyInputPromptInputMappingContext{ nullptr };

	UPROPERTY(EditDefaultsOnly)
	int32 PressAnyInputPromptInputPriority{ 15 };

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> PressAnyInputPromptAnyInputInputAction{ nullptr };

private:
	void SetupInput(TObjectPtr<UEnhancedInputComponent> InputComponent) override;
	TObjectPtr<UInputMappingContext> GetInputMappingContext() const override;
	int32 GetInputPriority() const override;

	void OnPressAnyInputPromptAnyInputTriggered(const FInputActionValue& Value);
};
