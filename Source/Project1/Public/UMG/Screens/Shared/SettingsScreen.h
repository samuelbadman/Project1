// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG/Screens/ScreenUserWidgetBase.h"
#include "SettingsScreen.generated.h"

class AProject1PlayerControllerBase;
struct FInputActionValue;
class UButtonMenuComponent;

/**
 * 
 */
UCLASS()
class PROJECT1_API USettingsScreen : public UScreenUserWidgetBase
{
	GENERATED_BODY()
	
private:
	UPROPERTY(BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UButtonMenuComponent> TabButtonMenuComponent;

	TObjectPtr<AProject1PlayerControllerBase> Project1PlayerController;
	FDelegateHandle TabInputDelegateHandle;
	FDelegateHandle CancelInputDelegateHandle;
	FDelegateHandle NavigateInputDelegateHandle;

public:
	USettingsScreen();

private:
	void NativeOnPushedToLayerStack() override;
	void NativeOnPoppedFromLayerStack() override;

	void OnTabInput(const FInputActionValue& Value);
	void OnCancelInput(const FInputActionValue& Value);
	void OnNavigateInput(const FInputActionValue& Value);
};
