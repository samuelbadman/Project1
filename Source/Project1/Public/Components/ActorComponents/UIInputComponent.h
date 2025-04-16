// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponents/Project1ActorComponentBase.h"
#include "GameplayTagContainer.h"
#include "UIInputComponent.generated.h"

class UEnhancedInputComponent;
class UUIInputBase;

/**
 * 
 */
UCLASS()
class PROJECT1_API UUIInputComponent : public UProject1ActorComponentBase
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly, meta = (DisplayName = "UI Inputs"))
	TMap<FGameplayTag, TObjectPtr<UUIInputBase>> UIInputs;

public:
	UUIInputComponent();

	void SetupUIInputComponent(TObjectPtr<UEnhancedInputComponent> InputComponent);
	TObjectPtr<UUIInputBase> GetUIInput(const FGameplayTag& Key) const;

	template<typename T>
	TObjectPtr<T> GetUIInputAs(const FGameplayTag& Key) const
	{
		return Cast<T>(GetUIInput(Key));
	}
};
