// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG/Screens/ScreenUserWidgetBase.h"
#include "InteractPromptScreen.generated.h"

class AGamePlayerController;
class UPlayerInteractComponent;
class UInteractPromptScreenUIInput;
class UHoldInteractManager;
class UProgressBar;
struct FInputActionValue;
struct FInteractableDescription;

/**
 *
 */
UCLASS()
class PROJECT1_API UInteractPromptScreen : public UScreenUserWidgetBase
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	FGameplayTag UIInputKey{};

	// Marked UPROPERTY as the hold interact manager object is owned by the interact prompt screen and should not be deleted by garbage collection 
	// until the owning interact prompt screen is deleted
	UPROPERTY()
	TObjectPtr<UHoldInteractManager> HoldInteractManager{ nullptr };

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

	TObjectPtr<AActor> TargetInteractable{ nullptr };

	TObjectPtr<UProgressBar> InteractProgressBar{ nullptr };

public:
	UInteractPromptScreen();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ShowSwitchActionPrompt(bool Show);

	UFUNCTION(BlueprintImplementableEvent)
	void SetInteractActionText(const FText& Text);

	UFUNCTION(BlueprintImplementableEvent)
	UProgressBar* GetInteractProgressBar();

private:
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

	// Hold interact type events bound to delegates in the hold interact manager object owned by this class
	void OnHoldInteractStarted();
	void OnHoldInteractTicked(float PercentComplete);
	void OnHoldInteractCanceled();
	void OnHoldInteractComplete();

	void UpdateInteractPromptUIForNewTargetInteractable(const FInteractableDescription& NewTargetInteractableDesc);
	void ClearInteractProgressBarProgress();
};
