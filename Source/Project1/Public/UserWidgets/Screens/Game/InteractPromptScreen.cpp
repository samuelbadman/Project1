// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractPromptScreen.h"
#include "Kismet/GameplayStatics.h"
#include "HUDs/Project1HUDBase.h"
#include "UserWidgets/Layers/LayerUserWidgetBase.h"
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

	// Get HUD
	Project1HUD = CastChecked<AProject1HUDBase>(GamePlayerController->GetHUD());

	// Get owning layer
	OwningLayer = Project1HUD->GetRegisteredPrimaryLayoutLayer(GetOwningLayerName());

	// Hide interact prompt in owning layer
	OwningLayer->CollapseTop();

	// Get player interact component and register to events
	PlayerInteractComponent->OnBeginInteractableOverlapDelegate.AddUObject(this, &UInteractPromptScreen::OnInteractableBeginPlayerOverlap);
	PlayerInteractComponent->OnEndInteractableOverlapDelegate.AddUObject(this, &UInteractPromptScreen::OnInteractableEndPlayerOverlap);
	PlayerInteractComponent->OnTargetInteractableChangedDelegate.AddUObject(this, &UInteractPromptScreen::OnTargetInteractableChanged);
}

void UInteractPromptScreen::NativeOnNavigateNoMoveNoRepeatTriggered(const FInputActionValue& Value)
{
	PlayerInteractComponent->IncrementTargetInteractableIndex(static_cast<int32>(Value.Get<FVector2D>().X));
}

void UInteractPromptScreen::NativeOnConfirmTriggered(const FInputActionValue& Value)
{
	if (TObjectPtr<AActor> TargetInteractable = PlayerInteractComponent->GetTargetInteractable())
	{
		IInteractable::Execute_OnInteractedWith(TargetInteractable, GamePlayerController->GetPawn());
	}
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

void UInteractPromptScreen::OnTargetInteractableChanged(TWeakObjectPtr<AActor> Interactable)
{
	SetInteractActionText(IInteractable::Execute_GetInteractActionText(Interactable.Get()));
}
