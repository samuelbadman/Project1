// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG/Screens/ScreenUserWidgetBase.h"
#include "GameplayTagContainer.h"
#include "SettingsScreen.generated.h"

class AProject1PlayerControllerBase;
struct FInputActionValue;
class UButtonMenuComponent;
class USettingsPageWidget;
class UInputMappingContext;
class USettingsScreenUIInput;

/**
 * 
 */
UCLASS()
class PROJECT1_API USettingsScreen : public UScreenUserWidgetBase
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Input", meta = (DisplayName = "UI Input Key"))
	FGameplayTag UIInputKey{};

	UPROPERTY(BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UButtonMenuComponent> TabButtonMenuComponent;

	TObjectPtr<AProject1PlayerControllerBase> Project1PlayerController;
	TObjectPtr<USettingsScreenUIInput> SettingsScreenUIInput;
	FDelegateHandle TabInputDelegateHandle;
	FDelegateHandle CancelInputDelegateHandle;
	FDelegateHandle NavigateInputDelegateHandle;
	FDelegateHandle ConfirmInputDelegateHandle;
	TObjectPtr<USettingsPageWidget> CurrentSettingsPage;

public:
	USettingsScreen();

	UFUNCTION(BlueprintCallable, Category = "SettingsScreen")
	void ChangeSettingsPage(USettingsPageWidget* NewPage);

private:
	void NativeOnPushedToLayerStack() override;
	void NativeOnPoppedFromLayerStack() override;

	void OnTabInput(const FInputActionValue& Value);
	void OnCancelInput(const FInputActionValue& Value);
	void OnNavigateInput(const FInputActionValue& Value);
	void OnConfirmInput(const FInputActionValue& Value);
};
