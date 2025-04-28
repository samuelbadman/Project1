// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/UIInput/Inputs/UIInputBase.h"
#include "SaveLoadScreenUIInput.generated.h"

struct FInputActionValue;
class UInputAction;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnCancelInputTriggeredDelegateSignature, const FInputActionValue& /*Value*/);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnConfirmInputTriggeredDelegateSignature, const FInputActionValue& /*Value*/);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnNavigateInputTriggeredDelegateSignature, const FInputActionValue& /*Value*/);

/**
 * 
 */
UCLASS()
class PROJECT1_API USaveLoadScreenUIInput : public UUIInputBase
{
	GENERATED_BODY()
	
public:
	FOnCancelInputTriggeredDelegateSignature OnCancelInputTriggeredDelegate;
	FOnConfirmInputTriggeredDelegateSignature OnConfirmInputTriggeredDelegate;
	FOnNavigateInputTriggeredDelegateSignature OnNavigateInputTriggeredDelegate;

private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> CancelInputAction;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> ConfirmInputAction;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> NavigateInputAction;

public:
	USaveLoadScreenUIInput();

private:
	void SetupInput(TObjectPtr<UEnhancedInputComponent> InputComponent) override;

	void OnCancelInputTriggered(const FInputActionValue& Value);
	void OnConfirmInputTriggered(const FInputActionValue& Value);
	void OnNavigateInputTriggered(const FInputActionValue& Value);
};
