// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserWidgets/Screens/ScreenUserWidgetBase.h"
#include "InteractPromptScreen.generated.h"

class AGamePlayerController;
class UPlayerInteractComponent;
class AProject1HUDBase;

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
	TObjectPtr<AProject1HUDBase> Project1HUD{ nullptr };
	TObjectPtr<ULayerUserWidgetBase> OwningLayer{ nullptr };

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ShowSwitchActionPrompt(bool Show);

	UFUNCTION(BlueprintImplementableEvent)
	void SetInteractActionText(const FText& Text);

private:
	// Called when the widget is pushed to a widget layer stack
	void NativeOnPushedToLayerStack() override;
	// Called when the widget is manually shown on top of a widget layer stack by calling ShowTop on the layer
	//void NativeOnShown() override;
	// Called when the widget is manually collapsed on top of a widget layer stack by calling CollapseTop on the layer
	//void NativeOnCollapsed() override;

	void NativeOnNavigateNoMoveNoRepeatTriggered(const FInputActionValue& Value) override;
	void NativeOnConfirmTriggered(const FInputActionValue& Value) override;

	void OnInteractableBeginPlayerOverlap(TWeakObjectPtr<AActor> Interactable, int32 NumOverlappedInteractables);
	void OnInteractableEndPlayerOverlap(TWeakObjectPtr<AActor> Interactable, int32 NumOverlappedInteractables);
	void OnTargetInteractableChanged(TWeakObjectPtr<AActor> Interactable);
};
