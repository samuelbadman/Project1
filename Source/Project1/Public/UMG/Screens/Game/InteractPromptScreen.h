// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG/Screens/ScreenUserWidgetBase.h"
#include "InteractPromptScreen.generated.h"

class AGamePlayerController;
class UPlayerInteractComponent;
class UInteractPromptScreenUIInput;
class UPressInteractionManager;
class UHoldInteractionManager;
class UMashInteractionManager;
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

	// Marked UPROPERTY as the press interaction manager object is owned by the interact prompt screen and should not be deleted by garbage collection 
	// until the owning interact prompt screen is deleted
	UPROPERTY()
	TObjectPtr<UPressInteractionManager> PressInteractionManager{ nullptr };

	// Marked UPROPERTY as the hold interaction manager object is owned by the interact prompt screen and should not be deleted by garbage collection 
	// until the owning interact prompt screen is deleted
	UPROPERTY()
	TObjectPtr<UHoldInteractionManager> HoldInteractionManager{ nullptr };

	// Marked UPROPERTY as the mash interaction manager object is owned by the interact prompt screen and should not be deleted by garbage collection 
	// until the owning interact prompt screen is deleted
	UPROPERTY()
	TObjectPtr<UMashInteractionManager> MashInteractionManager{ nullptr };

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

	// Press interaction type events bound to delegates in the hold interaction manager object owned by this class
	void OnPressInteractionStarted();
	void OnPressInteractionTicked(float PercentComplete);
	void OnPressInteractionCanceled();
	void OnPressInteractionComplete();

	// Hold interaction type events bound to delegates in the hold interaction manager object owned by this class
	void OnHoldInteractionStarted();
	void OnHoldInteractionTicked(float PercentComplete);
	void OnHoldInteractionCanceled();
	void OnHoldInteractionComplete();

	// Mash interaction type events bound to delegates in the hold interaction manager object owned by this class
	void OnMashInteractionStarted();
	void OnMashInteractionTicked(float PercentComplete);
	void OnMashInteractionCanceled();
	void OnMashInteractionComplete();

	void SetupPressInteractManager();
	void SetupHoldInteractManager();
	void SetupMashInteractManager();
	void UpdateInteractPromptUIForNewTargetInteractable(const FInteractableDescription& NewTargetInteractableDesc);
	void ClearInteractProgressBarProgress();
};
