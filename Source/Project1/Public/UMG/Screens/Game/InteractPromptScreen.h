// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG/Screens/ScreenUserWidgetBase.h"
#include "Structures/InteractableDescription.h"
#include "InteractPromptScreen.generated.h"

class AGamePlayerController;
class UPlayerInteractComponent;
class UInteractPromptScreenUIInput;
class UProgressBar;
class UInteractionBase;
struct FInputActionValue;
struct FInteractableDescription;

struct FTargetInteractableReference
{
	TObjectPtr<AActor> TargetInteractable{ nullptr };
	FInteractableDescription TargetInteractableDescription{};
};

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
	FTargetInteractableReference TargetInteractableReference{};

	// Marked UPROPERTY for garbage collection
	UPROPERTY()
	TObjectPtr<UInteractionBase> CurrentInteraction{ nullptr };

	// Current interaction callback delegate handles
	FDelegateHandle OnInteractionStartedDelegateHandle{};
	FDelegateHandle OnInteractionCompletedDelegateHandle{};
	FDelegateHandle OnInteractionCanceledDelegateHandle{};
	FDelegateHandle OnInteractionCompletionPercentChangedDelegateHandle{};

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

	void OnCurrentInteractionStarted(UInteractionBase* Interaction);
	void OnCurrentInteractionCompleted(UInteractionBase* Interaction);
	void OnCurrentInteractionCanceled(UInteractionBase* Interaction);
	void OnCurrentInteractionCompletionPercentChanged(UInteractionBase* Interaction);

	void UpdateUIForNewTargetInteractable(bool ShowInteractProgressBar);
	void SetInteractProgressBarProgress(float Percent);
	void ClearInteractProgressBarProgress();
	void BindInteractionEvents(UInteractionBase* Interaction);
	void UnBindInteractionEvents(UInteractionBase* Interaction);
	void SetNewCurrentInteraction(EInteractionType InteractionType);
	void ClearCurrentInteraction();
	void RemoveCurrentInteractionAndProgress();
};
