// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG/Screens/Widgets/Modals/ModalScreenBase.h"
#include "ConfirmModalScreen.generated.h"

class AProject1PlayerControllerBase;
class UProject1ButtonBase;
struct FInputActionValue;
class UButtonNavigationComponent;

/**
 * 
 */
UCLASS()
class PROJECT1_API UConfirmModalScreen : public UModalScreenBase
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	TObjectPtr<UButtonNavigationComponent> ButtonNavigationComponent{ nullptr };

	TObjectPtr<AProject1PlayerControllerBase> Project1PlayerController{ nullptr };

	FDelegateHandle ConfirmInputTriggeredDelegateHandle{};
	FDelegateHandle NavigateInputTriggeredDelegateHandle{};

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
	void OnOptionButtonHovered(UProject1ButtonBase* ButtonHovered);

	UFUNCTION()
	void OnOption1Selected(UProject1ButtonBase* ButtonSelected);
	UFUNCTION()
	void OnOption2Selected(UProject1ButtonBase* ButtonSelected);
};
