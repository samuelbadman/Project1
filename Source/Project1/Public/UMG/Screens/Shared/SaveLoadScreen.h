// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG/Screens/ScreenUserWidgetBase.h"
#include "GameplayTagContainer.h"
#include "SaveLoadScreen.generated.h"

class AProject1PlayerControllerBase;
class USaveLoadScreenUIInput;
class UButtonMenuComponent;
struct FInputActionValue;

/**
 * 
 */
UCLASS()
class USaveLoadScreen : public UScreenUserWidgetBase
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SaveLoadScreen", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UButtonMenuComponent> ButtonMenuComponent;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag UIInputKey;

	UPROPERTY(BlueprintReadOnly, Category = "SaveLoadScreen", meta = (AllowPrivateAccess = "true"))
	bool bInSaveMode;

	TObjectPtr<AProject1PlayerControllerBase> PlayerController;
	TObjectPtr<USaveLoadScreenUIInput> SaveLoadScreenUIInput;
	FDelegateHandle CancelInputDelegateHandle;
	FDelegateHandle ConfirmInputDelegateHandle;
	FDelegateHandle NavigateInputDelegateHandle;

public:
	USaveLoadScreen();

private:
	void NativeConsumeLoadPayload(TObjectPtr<UScreenWidgetLoadPayloadBase> LoadPayload) override;
	void NativeOnPushedToLayerStack() override;
	void NativeOnPoppedFromLayerStack() override;

	void OnCancelInputTriggered(const FInputActionValue& Value);
	void OnConfirmInputTriggered(const FInputActionValue& Value);
	void OnNavigateInputTriggered(const FInputActionValue& Value);
};
