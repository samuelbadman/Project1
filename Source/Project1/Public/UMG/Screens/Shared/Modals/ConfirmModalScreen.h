// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModalScreenBase.h"
#include "Objects/ScreenLoadPayloads/ConfirmModalScreenLoadPayload.h"
#include "GameplayTagContainer.h"
#include "ConfirmModalScreen.generated.h"

class AProject1PlayerControllerBase;
struct FInputActionValue;
class UButtonMenuComponent;
class UConfirmModalScreenUIInput;

/**
 * 
 */
UCLASS()
class PROJECT1_API UConfirmModalScreen : public UModalScreenBase
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Input", meta = (DisplayName = "UI Input Key"))
	FGameplayTag UIInputKey{};

	UPROPERTY()
	TObjectPtr<UButtonMenuComponent> ButtonMenuComponent;

	TObjectPtr<AProject1PlayerControllerBase> Project1PlayerController{ nullptr };
	TObjectPtr<UConfirmModalScreenUIInput> ConfirmModalUIInput{ nullptr };

	FDelegateHandle ConfirmInputTriggeredDelegateHandle{};
	FDelegateHandle NavigateInputTriggeredDelegateHandle{};

	FConfirmModalOptionSelectedDelegate Option1SelectedDelegate{};
	FConfirmModalOptionSelectedDelegate Option2SelectedDelegate{};

public:
	UConfirmModalScreen();

	UFUNCTION(BlueprintImplementableEvent)
	void SetModalPromptText(const FText& Text);

	UFUNCTION(BlueprintImplementableEvent)
	void SetOption1Text(const FText& Text);

	UFUNCTION(BlueprintImplementableEvent)
	void SetOption2Text(const FText& Text);

	UFUNCTION(BlueprintImplementableEvent)
	UProject1ButtonBase* GetOption1Button();

	UFUNCTION(BlueprintImplementableEvent)
	UProject1ButtonBase* GetOption2Button();

private:
	void NativeOnPushedToLayerStack() override;
	void NativeConsumeLoadPayload(TObjectPtr<UScreenWidgetLoadPayloadBase> LoadPayload) override;
	void NativeOnPoppedFromLayerStack() override;

	void OnConfirmInputTriggered(const FInputActionValue& Value);
	void OnNavigateInputTriggered(const FInputActionValue& Value);

	UFUNCTION()
	void OnOption1Selected(UProject1ButtonBase* ButtonSelected);
	UFUNCTION()
	void OnOption2Selected(UProject1ButtonBase* ButtonSelected);
};
