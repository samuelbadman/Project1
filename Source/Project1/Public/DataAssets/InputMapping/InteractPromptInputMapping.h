// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingAssetBase.h"
#include "InteractPromptInputMapping.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT1_API UInteractPromptInputMapping : public UInputMappingAssetBase
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputMappingContext> InputMappingContext{ nullptr };

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> InteractInputAction{ nullptr };

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> SwitchActionInputAction{ nullptr };

public:
	FORCEINLINE TObjectPtr<UInputMappingContext> GetInputMappingContext() const { return InputMappingContext; }
	FORCEINLINE TObjectPtr<UInputAction> GetInteractInputAction() const { return InteractInputAction; }
	FORCEINLINE TObjectPtr<UInputAction> GetSwitchActionInputAction() const { return SwitchActionInputAction; }
};
