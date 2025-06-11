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
#include "Objects/Interact/PressInteractionManager.h"
#include "Objects/Interact/HoldInteractionManager.h"
#include "Objects/Interact/MashInteractionManager.h"
#include "Components/ProgressBar.h"
#include "Structures/InteractableDescription.h"

UInteractPromptScreen::UInteractPromptScreen()
{
	// Create the press interact manager object
	PressInteractionManager = CreateDefaultSubobject<UPressInteractionManager>(FName(TEXT("PressInteractManager")));

	// Create the hold interact manager object
	HoldInteractionManager = CreateDefaultSubobject<UHoldInteractionManager>(FName(TEXT("HoldInteractManager")));

	// Create the mash interact manager object
	MashInteractionManager = CreateDefaultSubobject<UMashInteractionManager>(FName(TEXT("MashInteractManager")));
}

void UInteractPromptScreen::NativeOnPushedToLayerStack()
{
	// The interact prompt is persistent as long as the game primary layout widget is around. It is on its own widget layer and is always on top of its widget layer
	
	// Setup interact manager objects
	SetupPressInteractManager();
	SetupHoldInteractManager();
	SetupMashInteractManager();

	// Save a reference to the interact progress bar
	InteractProgressBar = GetInteractProgressBar();

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
	// Cleanup press interact manager
	PressInteractionManager->OnInteractionStartedDelegate.Unbind();
	PressInteractionManager->OnInteractionTickedDelegate.Unbind();
	PressInteractionManager->OnInteractionCanceledDelegate.Unbind();
	PressInteractionManager->OnInteractionCompleteDelegate.Unbind();

	// Cleanup hold interact manager
	HoldInteractionManager->OnInteractionStartedDelegate.Unbind();
	HoldInteractionManager->OnInteractionTickedDelegate.Unbind();
	HoldInteractionManager->OnInteractionCanceledDelegate.Unbind();
	HoldInteractionManager->OnInteractionCompleteDelegate.Unbind();

	// Cleanup mash interact manager
	MashInteractionManager->OnInteractionStartedDelegate.Unbind();
	MashInteractionManager->OnInteractionTickedDelegate.Unbind();
	MashInteractionManager->OnInteractionCanceledDelegate.Unbind();
	MashInteractionManager->OnInteractionCompleteDelegate.Unbind();

	// Cleanup UI input
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
	// Target interactable cannot change if currently in a hold interaction
	if (HoldInteractionManager->IsInHoldInteract())
	{
		return;
	}

	// Get new target interactable interactable description
	FInteractableDescription NewTargetInteractableDesc;
	IInteractable::Execute_GetInteractableDescription(NewTargetInteractable.Get(), NewTargetInteractableDesc);

	// Update interact prompt UI for new target interactable
	UpdateInteractPromptUIForNewTargetInteractable(NewTargetInteractableDesc);

	// Update target interactable
	TargetInteractable = PlayerInteractComponent->GetTargetInteractable();

	// Update the interact action text in the interact prompt UI
	SetInteractActionText(NewTargetInteractableDesc.InteractActionText);
}

void UInteractPromptScreen::OnInteractStarted(const FInputActionValue& Value)
{
	// Only want to handle inputs when the widget is on top of the owning layer
	if (!CanReceiveInput())
	{
		return;
	}

	// Do the appropriate procedure for starting the interaction type of the target interactable
	FInteractableDescription TargetInteractableDesc;
	IInteractable::Execute_GetInteractableDescription(TargetInteractable, TargetInteractableDesc);

	const TObjectPtr<AActor> Interactor{ GamePlayerController->GetPawn() };

	switch (TargetInteractableDesc.InteractionType)
	{
	case EInteractableInteractionType::Press:
		// Starting a press interact
		PressInteractionManager->StartInteraction(TargetInteractable, Interactor);
		break;

	case EInteractableInteractionType::Hold:
		// Starting a hold interact
		HoldInteractionManager->StartInteraction(TargetInteractable, Interactor);
		break;

	case EInteractableInteractionType::Mash:
		// Starting a mash interact

		break;
	}
}

void UInteractPromptScreen::OnInteractTriggered(const FInputActionValue& Value)
{
	// Only want to handle inputs when the widget is on top of the owning layer
	if (!CanReceiveInput())
	{
		return;
	}

	// Only want to use triggered events for hold interactions when in a hold interaction. 
	// Press or mash interactions only need to be fired once when the input starts and use the started event
	if (HoldInteractionManager->IsInHoldInteract())
	{
		HoldInteractionManager->TickInteraction(TargetInteractable, GamePlayerController->GetPawn());
	}
}

void UInteractPromptScreen::OnInteractCompleted(const FInputActionValue& Value)
{
	// Only want to handle inputs when the widget is on top of the owning layer
	if (!CanReceiveInput())
	{
		return;
	}

	// If the player is in a hold interact, notify the hold interact manager that the interact input has completed (been released)
	if (HoldInteractionManager->IsInHoldInteract())
	{
		HoldInteractionManager->OnInteractInputCompleted(GamePlayerController->GetPawn(), TargetInteractable);
	}
}

void UInteractPromptScreen::OnSwitchActionTriggered(const FInputActionValue& Value)
{
	// Only want to handle inputs when the widget is on top of the owning layer
	if (!CanReceiveInput())
	{
		return;
	}

	// Cannot switch interact actions when in a hold interact
	if (HoldInteractionManager->IsInHoldInteract())
	{
		return;
	}

	if (PlayerInteractComponent->GetNumOverlappedInteractables() > 1)
	{
		PlayerInteractComponent->IncrementTargetInteractableIndex(StaticCast<int32>(Value.Get<float>()));
	}
}

void UInteractPromptScreen::OnPressInteractionStarted()
{
}

void UInteractPromptScreen::OnPressInteractionTicked(float PercentComplete)
{
}

void UInteractPromptScreen::OnPressInteractionCanceled()
{
}

void UInteractPromptScreen::OnPressInteractionComplete()
{
}

void UInteractPromptScreen::OnHoldInteractionStarted()
{
}

void UInteractPromptScreen::OnHoldInteractionTicked(float PercentComplete)
{
	// TODO: Use this event to update a UI progress bar in the interact prompt screen UMG widget

	// Update hold interact progress bar percent
	// NOTE: Dividing by 100.0 here as the progress bar percent needs to be in the range 0.0 - 1.0. PercentComplete is in the range 0.0 - 100.0
	InteractProgressBar->SetPercent(PercentComplete / 100.0f);
}

void UInteractPromptScreen::OnHoldInteractionCanceled()
{
	ClearInteractProgressBarProgress();
}

void UInteractPromptScreen::OnHoldInteractionComplete()
{
	ClearInteractProgressBarProgress();
}

void UInteractPromptScreen::OnMashInteractionStarted()
{
}

void UInteractPromptScreen::OnMashInteractionTicked(float PercentComplete)
{
}

void UInteractPromptScreen::OnMashInteractionCanceled()
{
}

void UInteractPromptScreen::OnMashInteractionComplete()
{
}

void UInteractPromptScreen::SetupPressInteractManager()
{
	// Initialize the press interact manager object
	PressInteractionManager->Initialize();

	// Bind to hold interact manager delegate events
	PressInteractionManager->OnInteractionStartedDelegate.BindUObject(this, &UInteractPromptScreen::OnPressInteractionStarted);
	PressInteractionManager->OnInteractionTickedDelegate.BindUObject(this, &UInteractPromptScreen::OnPressInteractionTicked);
	PressInteractionManager->OnInteractionCanceledDelegate.BindUObject(this, &UInteractPromptScreen::OnPressInteractionCanceled);
	PressInteractionManager->OnInteractionCompleteDelegate.BindUObject(this, &UInteractPromptScreen::OnPressInteractionComplete);
}

void UInteractPromptScreen::SetupHoldInteractManager()
{
	// Initialize the hold interact manager object
	HoldInteractionManager->Initialize();

	// Bind to hold interact manager delegate events
	HoldInteractionManager->OnInteractionStartedDelegate.BindUObject(this, &UInteractPromptScreen::OnHoldInteractionStarted);
	HoldInteractionManager->OnInteractionTickedDelegate.BindUObject(this, &UInteractPromptScreen::OnHoldInteractionTicked);
	HoldInteractionManager->OnInteractionCanceledDelegate.BindUObject(this, &UInteractPromptScreen::OnHoldInteractionCanceled);
	HoldInteractionManager->OnInteractionCompleteDelegate.BindUObject(this, &UInteractPromptScreen::OnHoldInteractionComplete);
}

void UInteractPromptScreen::SetupMashInteractManager()
{
	// Initialize the mash interact manager object
	MashInteractionManager->Initialize();

	// Bind to hold interact manager delegate events
	MashInteractionManager->OnInteractionStartedDelegate.BindUObject(this, &UInteractPromptScreen::OnMashInteractionStarted);
	MashInteractionManager->OnInteractionTickedDelegate.BindUObject(this, &UInteractPromptScreen::OnMashInteractionTicked);
	MashInteractionManager->OnInteractionCanceledDelegate.BindUObject(this, &UInteractPromptScreen::OnMashInteractionCanceled);
	MashInteractionManager->OnInteractionCompleteDelegate.BindUObject(this, &UInteractPromptScreen::OnMashInteractionComplete);
}

void UInteractPromptScreen::UpdateInteractPromptUIForNewTargetInteractable(const FInteractableDescription& NewTargetInteractableDesc)
{
	// TODO: Switch input prompt to reresent the key needs to be held instead of just pressed

	// Show interact progress UI if the new target interactable is a hold or mash interaction otherwise, hide the progress UI for a press interaction
	switch (NewTargetInteractableDesc.InteractionType)
	{
	case EInteractableInteractionType::Press:
		InteractProgressBar->SetVisibility(ESlateVisibility::Collapsed);
		break;

	case EInteractableInteractionType::Hold:
	case EInteractableInteractionType::Mash:
		InteractProgressBar->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		break;
	}
}

void UInteractPromptScreen::ClearInteractProgressBarProgress()
{
	InteractProgressBar->SetPercent(0.0f);
}
