// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/InputMapping/InputMappingAssetBase.h"
#include "MainMenuScreenInputMapping.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT1_API UMainMenuScreenInputMapping : public UInputMappingAssetBase
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputMappingContext> InputMappingContext{ nullptr };

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> ConfirmInputAction{ nullptr };

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> NavigateInputAction{ nullptr };

public:
	FORCEINLINE TObjectPtr<UInputMappingContext> GetInputMappingContext() const { return InputMappingContext; }
	FORCEINLINE TObjectPtr<UInputAction> GetConfirmInputAction() const { return ConfirmInputAction; }
	FORCEINLINE TObjectPtr<UInputAction> GetNavigateInputAction() const { return NavigateInputAction; }
};
