// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG/Screens/Modals/ModalScreenBase.h"
#include "DynamicModalScreen.generated.h"

class UVerticalBox;
class UDynamicModalOptionUserWidget;
class AProject1PlayerControllerBase;
struct FInputActionValue;
class UProject1ButtonBase;
class FDynamicModalOptionSelectedDelegate;

/**
 * 
 */
UCLASS()
class PROJECT1_API UDynamicModalScreen : public UModalScreenBase
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly)
	TSoftClassPtr<UDynamicModalOptionUserWidget> DynamicModalOptionWidgetClass{ nullptr };

	UPROPERTY(EditDefaultsOnly)
	FMargin OptionSpacerPadding{};

	TObjectPtr<AProject1PlayerControllerBase> Project1PlayerController{ nullptr };
	FDelegateHandle OnConfirmTriggeredDelegateHandle{};
	FDelegateHandle OnNavigateTriggeredDelegateHandle{};
	TArray<TPair<TObjectPtr<UDynamicModalOptionUserWidget>, FDynamicModalOptionSelectedDelegate>> ModalOptions{};

public:
	UDynamicModalScreen();

	UFUNCTION(BlueprintImplementableEvent)
	UVerticalBox* GetDynamicOptionContainer();

	UFUNCTION(BlueprintImplementableEvent)
	void SetModalPromptText(const FText& Text);

private:
	void NativeOnPushedToLayerStack() override;
	void NativeOnPoppedFromLayerStack() override;
	void NativeConsumeLoadPayload(TObjectPtr<UScreenWidgetLoadPayloadBase> LoadPayload) override;

	void OnConfirmTriggered(const FInputActionValue& Value);
	void OnNavigateTriggered(const FInputActionValue& Value);

	UFUNCTION()
	void OnOptionButtonHovered(UProject1ButtonBase* ButtonHovered);

	UFUNCTION()
	void OnOptionButtonSelected(UProject1ButtonBase* ButtonSelected);
};
