// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/UIInput/Inputs/UIInputBase.h"
#include "GameMenuScreenUIInput.generated.h"

struct FInputActionValue;
class UInputAction;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnConfirmTriggeredDelegate, const FInputActionValue& /* Value */);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnNavigateTriggeredDelegate, const FInputActionValue& /* Value */);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnCancelTriggeredDelegate, const FInputActionValue& /* Value */);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnQuitTriggeredDelegate, const FInputActionValue& /* Value */);

/**
 * 
 */
UCLASS()
class UGameMenuScreenUIInput : public UUIInputBase
{
	GENERATED_BODY()
	
public:
	FOnConfirmTriggeredDelegate ConfirmTriggered{};
	FOnNavigateTriggeredDelegate NavigateTriggered{};
	FOnCancelTriggeredDelegate CancelTriggered{};
	FOnQuitTriggeredDelegate QuitTriggered{};

private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputMappingContext> InputMappingContext{ nullptr };

	UPROPERTY(EditDefaultsOnly)
	int32 InputPriority{ 0 };

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> ConfirmInputAction{ nullptr };

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> NavigateInputAction{ nullptr };

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> CancelInputAction{ nullptr };

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> QuitInputAction{ nullptr };

private:
	void SetupInput(TObjectPtr<UEnhancedInputComponent> InputComponent) override;
	TObjectPtr<UInputMappingContext> GetInputMappingContext() const override;
	int32 GetInputPriority() const override;

	void OnConfirmTriggered(const FInputActionValue& Value);
	void OnNavigateTriggered(const FInputActionValue& Value);
	void OnCancelTriggered(const FInputActionValue& Value);
	void OnQuitTriggered(const FInputActionValue& Value);
};
