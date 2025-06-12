// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG/Screens/ScreenUserWidgetBase.h"
#include "InteractPromptScreen.generated.h"

class AGamePlayerController;
class UPlayerInteractComponent;
class UInteractPromptScreenUIInput;
class UProgressBar;
struct FInputActionValue;
struct FInteractableDescription;

/**
 * The interact prompt screen is a part of the game's interaction system allowing the player to interact with interactable objects in the game world.
 */
UCLASS()
class PROJECT1_API UInteractPromptScreen : public UScreenUserWidgetBase
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	FGameplayTag UIInputKey{};

	TObjectPtr<AGamePlayerController> GamePlayerController{ nullptr };
	TObjectPtr<UInteractPromptScreenUIInput> InteractPromptScreenUIInput{ nullptr };
	TObjectPtr<UPlayerInteractComponent> PlayerInteractComponent{ nullptr };
	TObjectPtr<ULayerUserWidgetBase> OwningLayer{ nullptr };

	FDelegateHandle OnBeginInteractablePlayerOverlapDelegateHandle{};
	FDelegateHandle OnEndInteractablePlayerOverlapDelegateHandle{};
	FDelegateHandle OnTargetInteractableChangedDelegateHandle{};

	FDelegateHandle OnInteractStartedDelegateHandle{};
	FDelegateHandle OnInteractTriggeredDelegateHandle{};
	FDelegateHandle OnInteractCompletedDelegateHandle{};
	FDelegateHandle OnSwitchActionTriggeredDelegateHandle{};

	TObjectPtr<UProgressBar> InteractProgressBar{ nullptr };

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ShowSwitchActionPrompt(bool Show);

	UFUNCTION(BlueprintImplementableEvent)
	void SetInteractActionText(const FText& Text);

	UFUNCTION(BlueprintImplementableEvent)
	UProgressBar* GetInteractProgressBar();

private:
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void NativeOnPushedToLayerStack() override;
	void NativeOnShown() override;
	void NativeOnCollapsed() override;
	void NativeOnPoppedFromLayerStack() override;

	void OnInteractableBeginPlayerOverlap(TWeakObjectPtr<AActor> Interactable, int32 NumOverlappedInteractables);
	void OnInteractableEndPlayerOverlap(TWeakObjectPtr<AActor> Interactable, int32 NumOverlappedInteractables);
	void OnTargetInteractableChanged(TWeakObjectPtr<AActor> NewTargetInteractable);

	void OnInteractStarted(const FInputActionValue& Value);
	void OnInteractTriggered(const FInputActionValue& Value);
	void OnInteractCompleted(const FInputActionValue& Value);
	void OnSwitchActionTriggered(const FInputActionValue& Value);

	void UpdateUIForNewTargetInteractable(bool ShowInteractProgressBar);
	void ClearInteractProgressBarProgress();
};
