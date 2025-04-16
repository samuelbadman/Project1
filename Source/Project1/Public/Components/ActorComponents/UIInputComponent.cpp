// Fill out your copyright notice in the Description page of Project Settings.


#include "UIInputComponent.h"
#include "Objects/UIInput/Inputs/SettingsScreenUIInput.h"
#include "EnhancedInputComponent.h"

UUIInputComponent::UUIInputComponent()
	:
	UIInputs({})
{
}

void UUIInputComponent::SetupUIInputComponent(TObjectPtr<UEnhancedInputComponent> InputComponent)
{
	for (const TPair<FGameplayTag, TObjectPtr<UUIInputBase>>& UIInput : UIInputs)
	{
		UIInput.Value->SetupInput(InputComponent);
	}
}

TObjectPtr<UUIInputBase> UUIInputComponent::GetUIInput(const FGameplayTag& Key) const
{
	return UIInputs[Key];
}
