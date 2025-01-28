// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/InputMapping/InputMappingAssetBase.h"
#include "PressAnyInputPromptInputMapping.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT1_API UPressAnyInputPromptInputMapping : public UInputMappingAssetBase
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputMappingContext> InputMappingContext{ nullptr };

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> AnyInputInputAction{ nullptr };

public:
	FORCEINLINE TObjectPtr<UInputMappingContext> GetInputMappingContext() const { return InputMappingContext; }
	FORCEINLINE TObjectPtr<UInputAction> GetAnyInputInputAction() const { return AnyInputInputAction; }
};
