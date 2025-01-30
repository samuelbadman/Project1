// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG/Screens/ScreenUserWidgetBase.h"
#include "DialogueScreen.generated.h"

class AGamePlayerController;
struct FInputActionValue;
class UDialogueManagerBase;
class UDialogueNode;

/**
 * 
 */
UCLASS()
class PROJECT1_API UDialogueScreen : public UScreenUserWidgetBase
{
	GENERATED_BODY()
	
private:
	TObjectPtr<UDialogueManagerBase> DialogueManager{ nullptr };
	TObjectPtr<AGamePlayerController> GamePlayerController{ nullptr };
	FDelegateHandle ConfirmTriggeredDelegateHandle{};
	FDelegateHandle DialogueNodePlayedDelegateHandle{};

public:
	UFUNCTION(BlueprintImplementableEvent)
	void SetDialogueLineText(const FText& Text);

private:
	void NativeOnPushedToLayerStack() override;
	void NativeOnPoppedFromLayerStack() override;
	void NativeConsumeLoadPayload(TObjectPtr<UScreenWidgetLoadPayloadBase> LoadPayload) override;

	void OnConfirmTriggered(const FInputActionValue& Value);
	void OnDialogueNodePlayed(const TObjectPtr<UDialogueNode> DialogueNode);
};
