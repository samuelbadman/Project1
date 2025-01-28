// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractPromptScreen.h"
#include "Kismet/GameplayStatics.h"
#include "HUDs/Project1HUDBase.h"
#include "UMG/Layers/LayerUserWidgetBase.h"
#include "PlayerControllers/GamePlayerController.h"
#include "Components/ActorComponents/PlayerInteractComponent.h"
#include "Interfaces/Interactable.h"
#include "InputActionValue.h"

void UInteractPromptScreen::NativeOnPushedToLayerStack()
{
	// The interact prompt is persistent as long as the game primary layout widget is around. It is always the top of the widget layer

	// Get game player controller
	GamePlayerController = CastChecked<AGamePlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	// Get player interact component
	PlayerInteractComponent = GamePlayerController->GetPlayerInteractComponent();

	// Get owning layer
	OwningLayer = CastChecked<AProject1HUDBase>(GamePlayerController->GetHUD())->GetRegisteredPrimaryLayoutWidgetLayer(GetOwningLayerName());

	// Hide interact prompt in owning layer
	OwningLayer->CollapseTop();

	// Register to events
	OnBeginInteractablePlayerOverlapDelegateHandle =
		PlayerInteractComponent->OnBeginInteractableOverlapDelegate.AddUObject(this, &UInteractPromptScreen::OnInteractableBeginPlayerOverlap);
	OnEndInteractablePlayerOverlapDelegateHandle =
		PlayerInteractComponent->OnEndInteractableOverlapDelegate.AddUObject(this, &UInteractPromptScreen::OnInteractableEndPlayerOverlap);
	OnTargetInteractableChangedDelegateHandle =
		PlayerInteractComponent->OnTargetInteractableChangedDelegate.AddUObject(this, &UInteractPromptScreen::OnTargetInteractableChanged);

	GamePlayerController->InteractPromptInteractTriggered.AddUObject(this, &UInteractPromptScreen::OnInteractTriggered);
	GamePlayerController->InteractPromptSwitchActionTriggered.AddUObject(this, &UInteractPromptScreen::OnSwitchActionTriggered);
}

void UInteractPromptScreen::NativeOnShown()
{
	GamePlayerController->AddInteractPromptInputMappingContext();
}

void UInteractPromptScreen::NativeOnCollapsed()
{
	GamePlayerController->RemoveInteractPromptInputMappingContext();
}

void UInteractPromptScreen::NativeOnPoppedFromLayerStack()
{
	PlayerInteractComponent->OnBeginInteractableOverlapDelegate.Remove(OnBeginInteractablePlayerOverlapDelegateHandle);
	OnBeginInteractablePlayerOverlapDelegateHandle.Reset();

	PlayerInteractComponent->OnEndInteractableOverlapDelegate.Remove(OnEndInteractablePlayerOverlapDelegateHandle);
	OnEndInteractablePlayerOverlapDelegateHandle.Reset();

	PlayerInteractComponent->OnTargetInteractableChangedDelegate.Remove(OnTargetInteractableChangedDelegateHandle);
	OnTargetInteractableChangedDelegateHandle.Reset();

	GamePlayerController->InteractPromptInteractTriggered.Remove(OnInteractTriggeredDelegateHandle);
	OnInteractTriggeredDelegateHandle.Reset();

	GamePlayerController->InteractPromptSwitchActionTriggered.Remove(OnSwitchActionTriggeredDelegateHandle);
	OnSwitchActionTriggeredDelegateHandle.Reset();
}

void UInteractPromptScreen::OnInteractableBeginPlayerOverlap(TWeakObjectPtr<AActor> Interactable, int32 NumOverlappedInteractables)
{
	// Show interact prompt screen
	OwningLayer->ShowTop();

	if (NumOverlappedInteractables > 1)
	{
		ShowSwitchActionPrompt(true);
	}
}

void UInteractPromptScreen::OnInteractableEndPlayerOverlap(TWeakObjectPtr<AActor> Interactable, int32 NumOverlappedInteractables)
{
	if (NumOverlappedInteractables == 0)
	{
		// Collapse interact prompt screen
		OwningLayer->CollapseTop();
	}
	else if (NumOverlappedInteractables == 1)
	{
		ShowSwitchActionPrompt(false);
	}
}

void UInteractPromptScreen::OnTargetInteractableChanged(TWeakObjectPtr<AActor> NewTargetInteractable)
{
	SetInteractActionText(IInteractable::Execute_GetInteractActionText(NewTargetInteractable.Get()));
}

void UInteractPromptScreen::OnInteractTriggered(const FInputActionValue& Value)
{
	// Only want to handle inputs when the widget is on top of the owning layer
	if (CanReceiveInput())
	{
		if (const TObjectPtr<AActor> TargetInteractable = PlayerInteractComponent->GetTargetInteractable())
		{
			IInteractable::Execute_OnInteractedWith(TargetInteractable, GamePlayerController->GetPawn());
		}
	}
}

void UInteractPromptScreen::OnSwitchActionTriggered(const FInputActionValue& Value)
{
	// Only want to handle inputs when the widget is on top of the owning layer
	if(CanReceiveInput())
	{
		if (PlayerInteractComponent->GetNumOverlappedInteractables() > 1)
		{
			PlayerInteractComponent->IncrementTargetInteractableIndex(static_cast<int32>(Value.Get<float>()));
		}
	}
}
