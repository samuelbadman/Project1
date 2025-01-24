// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserWidgets/Screens/Widgets/ScreenUserWidgetBase.h"
#include "InteractPromptScreen.generated.h"

class AGamePlayerController;
class UPlayerInteractComponent;
struct FInputActionValue;

/**
 *
 */
UCLASS()
class PROJECT1_API UInteractPromptScreen : public UScreenUserWidgetBase
{
	GENERATED_BODY()

private:
	TObjectPtr<AGamePlayerController> GamePlayerController{ nullptr };
	TObjectPtr<UPlayerInteractComponent> PlayerInteractComponent{ nullptr };
	TObjectPtr<ULayerUserWidgetBase> OwningLayer{ nullptr };

	FDelegateHandle OnBeginInteractablePlayerOverlapDelegateHandle{};
	FDelegateHandle OnEndInteractablePlayerOverlapDelegateHandle{};
	FDelegateHandle OnTargetInteractableChangedDelegateHandle{};

	FDelegateHandle OnInteractTriggeredDelegateHandle{};
	FDelegateHandle OnSwitchActionTriggeredDelegateHandle{};

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ShowSwitchActionPrompt(bool Show);

	UFUNCTION(BlueprintImplementableEvent)
	void SetInteractActionText(const FText& Text);

private:
	void NativeOnPushedToLayerStack() override;
	void NativeOnShown() override;
	void NativeOnCollapsed() override;
	void NativeOnPoppedFromLayerStack() override;

	void OnInteractableBeginPlayerOverlap(TWeakObjectPtr<AActor> Interactable, int32 NumOverlappedInteractables);
	void OnInteractableEndPlayerOverlap(TWeakObjectPtr<AActor> Interactable, int32 NumOverlappedInteractables);
	void OnTargetInteractableChanged(TWeakObjectPtr<AActor> NewTargetInteractable);

	void OnInteractTriggered(const FInputActionValue& Value);
	void OnSwitchActionTriggered(const FInputActionValue& Value);
};
