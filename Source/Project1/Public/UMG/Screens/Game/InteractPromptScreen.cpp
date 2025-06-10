// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractPromptScreen.h"
#include "Kismet/GameplayStatics.h"
#include "HUDs/Project1HUDBase.h"
#include "UMG/Layers/LayerUserWidgetBase.h"
#include "Controllers/PlayerControllers/GamePlayerController.h"
#include "Components/ActorComponents/PlayerInteractComponent.h"
#include "Interfaces/Interactable.h"
#include "InputActionValue.h"
#include "Objects/UIInput/Inputs/InteractPromptScreenUIInput.h"
#include "Components/ActorComponents/UIInputComponent.h"
#include "Objects/Interact/LongPressInteractManager.h"

UInteractPromptScreen::UInteractPromptScreen()
{
	// Create the long press interact manager object
	LongPressInteractManager = CreateDefaultSubobject<ULongPressInteractManager>(FName(TEXT("LongPressInteractManager")));
}

void UInteractPromptScreen::NativeOnPushedToLayerStack()
{
	// The interact prompt is persistent as long as the game primary layout widget is around. It is on its own widget layer and is always on top of its widget layer

	// Initialize the long press interact manager object
	LongPressInteractManager->Initialize();

	// Bind to long press interact manager interact ticked delegate
	LongPressInteractManager->OnLongPressInteractTickedDelegate.BindUObject(this, &UInteractPromptScreen::OnLongPressInteractTicked);

	// Get player controller
	GamePlayerController = Cast<AGamePlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	if (IsValid(GamePlayerController))
	{
		// Get interact prompt screen UI input
		InteractPromptScreenUIInput = GamePlayerController->GetUIInputComponent()->GetUIInputAs<UInteractPromptScreenUIInput>(UIInputKey);

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

		OnInteractStartedDelegateHandle = InteractPromptScreenUIInput->InteractStarted.AddUObject(this, &UInteractPromptScreen::OnInteractStarted);
		OnInteractTriggeredDelegateHandle = InteractPromptScreenUIInput->InteractTriggered.AddUObject(this, &UInteractPromptScreen::OnInteractTriggered);
		OnInteractCompletedDelegateHandle = InteractPromptScreenUIInput->InteractCompleted.AddUObject(this, &UInteractPromptScreen::OnInteractCompleted);
		OnSwitchActionTriggeredDelegateHandle = InteractPromptScreenUIInput->SwitchActionTriggered.AddUObject(this, &UInteractPromptScreen::OnSwitchActionTriggered);
	}
}

void UInteractPromptScreen::NativeOnShown()
{
	InteractPromptScreenUIInput->Add(GamePlayerController->GetEnhancedInputLocalPlayerSubsystem());
}

void UInteractPromptScreen::NativeOnCollapsed()
{
	InteractPromptScreenUIInput->Remove(GamePlayerController->GetEnhancedInputLocalPlayerSubsystem());
}

void UInteractPromptScreen::NativeOnPoppedFromLayerStack()
{
	LongPressInteractManager->OnLongPressInteractTickedDelegate.Unbind();

	PlayerInteractComponent->OnBeginInteractableOverlapDelegate.Remove(OnBeginInteractablePlayerOverlapDelegateHandle);
	OnBeginInteractablePlayerOverlapDelegateHandle.Reset();

	PlayerInteractComponent->OnEndInteractableOverlapDelegate.Remove(OnEndInteractablePlayerOverlapDelegateHandle);
	OnEndInteractablePlayerOverlapDelegateHandle.Reset();

	PlayerInteractComponent->OnTargetInteractableChangedDelegate.Remove(OnTargetInteractableChangedDelegateHandle);
	OnTargetInteractableChangedDelegateHandle.Reset();

	InteractPromptScreenUIInput->InteractStarted.Remove(OnInteractStartedDelegateHandle);
	OnInteractStartedDelegateHandle.Reset();

	InteractPromptScreenUIInput->InteractTriggered.Remove(OnInteractTriggeredDelegateHandle);
	OnInteractTriggeredDelegateHandle.Reset();

	InteractPromptScreenUIInput->InteractCompleted.Remove(OnInteractCompletedDelegateHandle);
	OnInteractCompletedDelegateHandle.Reset();

	InteractPromptScreenUIInput->SwitchActionTriggered.Remove(OnSwitchActionTriggeredDelegateHandle);
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
	// Target interactable cannot change if currently in a long press interaction
	if (LongPressInteractManager->IsInLongPressInteract())
	{
		return;
	}

	// TODO: Can use this event to check here if the new target interactable is a long press one and update UI accordingly

	// Update target interactable
	TargetInteractable = PlayerInteractComponent->GetTargetInteractable();

	// Update the interact action text in the interact prompt UI
	SetInteractActionText(IInteractable::Execute_GetInteractActionText(NewTargetInteractable.Get()));
}

void UInteractPromptScreen::OnInteractStarted(const FInputActionValue& Value)
{
	// Only want to handle inputs when the widget is on top of the owning layer
	if (!CanReceiveInput())
	{
		return;
	}

	// Does the target interactable require a long or single press interact?
	if (IInteractable::Execute_IsLongPressInteract(TargetInteractable))
	{
		// Starting a long press interact
		LongPressInteractManager->StartLongPressInteract(GamePlayerController->GetPawn(), TargetInteractable);
	}
	else
	{
		// Starting a single press interact. Interact with the interactable
		IInteractable::Execute_OnInteractedWith(TargetInteractable, GamePlayerController->GetPawn());
	}
}

void UInteractPromptScreen::OnInteractTriggered(const FInputActionValue& Value)
{
	// Only want to handle inputs when the widget is on top of the owning layer
	if (!CanReceiveInput())
	{
		return;
	}

	// Only want to use triggered events for long press interactions when in a long press interaction. 
	// Single press interactions only need to be fired once when the input starts and use the started event
	if (LongPressInteractManager->IsInLongPressInteract())
	{
		LongPressInteractManager->TickLongPressInteract(GamePlayerController->GetPawn());
	}
}

void UInteractPromptScreen::OnInteractCompleted(const FInputActionValue& Value)
{
	// Only want to handle inputs when the widget is on top of the owning layer
	if (!CanReceiveInput())
	{
		return;
	}

	// If the player is in a long press interact, notify the long press interact manager that the interact input has completed (been released)
	if (LongPressInteractManager->IsInLongPressInteract())
	{
		LongPressInteractManager->OnInteractInputCompleted(GamePlayerController->GetPawn(), TargetInteractable);
	}
}

void UInteractPromptScreen::OnSwitchActionTriggered(const FInputActionValue& Value)
{
	// Only want to handle inputs when the widget is on top of the owning layer
	if (!CanReceiveInput())
	{
		return;
	}

	// Cannot switch interact actions when in a long press interact
	if (LongPressInteractManager->IsInLongPressInteract())
	{
		return;
	}

	if (PlayerInteractComponent->GetNumOverlappedInteractables() > 1)
	{
		PlayerInteractComponent->IncrementTargetInteractableIndex(StaticCast<int32>(Value.Get<float>()));
	}
}

void UInteractPromptScreen::OnLongPressInteractTicked(float PercentComplete)
{
	// TODO: Use this event to update a UI progress bar in the interact prompt screen UMG widget
}
