// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/UIInput/Inputs/UIInputBase.h"
#include "DialogueScreenUIInput.generated.h"

struct FInputActionValue;
class UInputAction;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnConfirmTriggeredDelegate, const FInputActionValue& /* Value */);

/**
 * 
 */
UCLASS()
class PROJECT1_API UDialogueScreenUIInput : public UUIInputBase
{
	GENERATED_BODY()
	
public:
	FOnConfirmTriggeredDelegate ConfirmTriggered{};

private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> ConfirmInputAction{ nullptr };

private:
	void SetupInput(TObjectPtr<UEnhancedInputComponent> InputComponent) override;

	void OnConfirmTriggered(const FInputActionValue& Value);
};
