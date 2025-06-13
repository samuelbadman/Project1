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
#include "Components/ProgressBar.h"
#include "Structures/InteractableDescription.h"
#include "FunctionLibraries/Project1GameplayLibrary.h"
#include "Interactions/InteractionBase.h"

void UInteractPromptScreen::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// Tick the current interaction if there is one
	if (IsValid(CurrentInteraction))
	{
		CurrentInteraction->Tick(InDeltaTime);
	}
}

void UInteractPromptScreen::NativeOnPushedToLayerStack()
{
	// The interact prompt is persistent as long as the game primary layout widget is around. It is on its own widget layer and is always on top of its widget layer

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

		// Register to interact system events
		OnBeginInteractablePlayerOverlapDelegateHandle =
			PlayerInteractComponent->OnBeginInteractableOverlapDelegate.AddUObject(this, &UInteractPromptScreen::OnInteractableBeginPlayerOverlap);
		OnEndInteractablePlayerOverlapDelegateHandle =
			PlayerInteractComponent->OnEndInteractableOverlapDelegate.AddUObject(this, &UInteractPromptScreen::OnInteractableEndPlayerOverlap);
		OnTargetInteractableChangedDelegateHandle =
			PlayerInteractComponent->OnTargetInteractableChangedDelegate.AddUObject(this, &UInteractPromptScreen::OnTargetInteractableChanged);

		// Register to interact screen UI input events
		OnInteractionStartedDelegateHandle = InteractPromptScreenUIInput->InteractStarted.AddUObject(this, &UInteractPromptScreen::OnInteractStarted);
		OnInteractTriggeredDelegateHandle = InteractPromptScreenUIInput->InteractTriggered.AddUObject(this, &UInteractPromptScreen::OnInteractTriggered);
		OnInteractCompletedDelegateHandle = InteractPromptScreenUIInput->InteractCompleted.AddUObject(this, &UInteractPromptScreen::OnInteractCompleted);
		OnSwitchActionTriggeredDelegateHandle = InteractPromptScreenUIInput->SwitchActionTriggered.AddUObject(this, &UInteractPromptScreen::OnSwitchActionTriggered);
	}
}

void UInteractPromptScreen::NativeOnShown()
{
	// Add UI input mapping context
	InteractPromptScreenUIInput->Add(GamePlayerController->GetEnhancedInputLocalPlayerSubsystem());
}

void UInteractPromptScreen::NativeOnCollapsed()
{
	// Remove UI input mapping context
	InteractPromptScreenUIInput->Remove(GamePlayerController->GetEnhancedInputLocalPlayerSubsystem());
}

void UInteractPromptScreen::NativeOnPoppedFromLayerStack()
{
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
	// Don't allow interactable change if the player is currently in an interaction
	if ((IsValid(CurrentInteraction)) && (!CurrentInteraction->IsComplete()))
	{
		// NOTE: This assumes interactables that have a duration such as hold and tap are not placed near to each other and the player cannot move away whilst in an interaction
		// with a duration
		return;
	}

	// Update target interactable pointer and description
	const TObjectPtr<AActor> NewTargetInteractablePtr{ NewTargetInteractable.Get() };
	TargetInteractableReference.TargetInteractable = NewTargetInteractablePtr;
	IInteractable::Execute_GetInteractableDescription(NewTargetInteractablePtr, TargetInteractableReference.TargetInteractableDescription);

	// Update interact prompt UI for new target interactable
	UpdateUIForNewTargetInteractable(TargetInteractableReference.TargetInteractableDescription.InteractionType == EInteractionType::Hold ||
		TargetInteractableReference.TargetInteractableDescription.InteractionType == EInteractionType::Tap);

	// Update the interact action text in the interact prompt UI
	SetInteractActionText(FText::FromString(TargetInteractableReference.TargetInteractableDescription.InteractActionText.ToString()));

	// Notify the interactable it has become targeted for interaction by the player
	IInteractable::Execute_OnBecomeTargetedInteractable(NewTargetInteractablePtr, GamePlayerController->GetPawn());
}

void UInteractPromptScreen::OnInteractStarted(const FInputActionValue& Value)
{
	// Only want to handle inputs when the widget is on top of the owning layer
	if (!CanReceiveInput())
	{
		return;
	}

	// The interact input has been pressed

	// Pass interact input pressed event to current interaction if there is one
	if (IsValid(CurrentInteraction))
	{
		// Pass the current interaction the input event
		CurrentInteraction->OnInteractInputPressed();
	}
	// Otherwise, create a new interaction, set it as the current interactionand pass it the interact input pressed event
	else
	{
		// Create new interaction and set as current interaction
		SetNewCurrentInteraction(TargetInteractableReference.TargetInteractableDescription.InteractionType);

		// Initialize the new interaction
		FInteractionDescription InteractionDesc{};

		switch (TargetInteractableReference.TargetInteractableDescription.InteractionType)
		{
		case EInteractionType::Hold:
			InteractionDesc.HoldDurationSeconds = TargetInteractableReference.TargetInteractableDescription.HoldInteractionDurationSeconds;
			break;

		case EInteractionType::Tap:
			InteractionDesc.TapIncrementAmount = TargetInteractableReference.TargetInteractableDescription.TapInteractionPercentCompleteIncrementAmount;
			InteractionDesc.TapIncrementAmountCurveModifier = TargetInteractableReference.TargetInteractableDescription.TapInteractionIncrementAmountCurveModifier;
			InteractionDesc.TapDecayRate = TargetInteractableReference.TargetInteractableDescription.TapInteractionDecayRate;
			break;

		default:
			break;
		}

		CurrentInteraction->Initialize(InteractionDesc);

		// Pass the current interaction the input event
		CurrentInteraction->OnInteractInputPressed();
	}
}

void UInteractPromptScreen::OnInteractTriggered(const FInputActionValue& Value)
{
	// Only want to handle inputs when the widget is on top of the owning layer
	if (!CanReceiveInput())
	{
		return;
	}

	// The interact input is being held down

	// Pass the interact input held event to the current interaction if there is one
	if (IsValid(CurrentInteraction))
	{
		CurrentInteraction->OnInteractInputHeld(GetWorld()->GetDeltaSeconds());
	}
}

void UInteractPromptScreen::OnInteractCompleted(const FInputActionValue& Value)
{
	// Only want to handle inputs when the widget is on top of the owning layer
	if (!CanReceiveInput())
	{
		return;
	}

	// The interact input has been released

	// Pass the interact input released event to the current interaction if there is one
	if (IsValid(CurrentInteraction))
	{
		CurrentInteraction->OnInteractInputReleased();
	}
}

void UInteractPromptScreen::OnSwitchActionTriggered(const FInputActionValue& Value)
{
	// Only want to handle inputs when the widget is on top of the owning layer
	if (!CanReceiveInput())
	{
		return;
	}

	// Cannot switch interact actions when in a current in-progress interaction
	if (IsValid(CurrentInteraction))
	{
		return;
	}

	// Switch interact action
	if (PlayerInteractComponent->GetNumOverlappedInteractables() > 1)
	{
		PlayerInteractComponent->IncrementTargetInteractableIndex(StaticCast<int32>(Value.Get<float>()));
	}
}

void UInteractPromptScreen::OnCurrentInteractionStarted(UInteractionBase* Interaction)
{
	IInteractable::Execute_OnInteractionStarted(TargetInteractableReference.TargetInteractable, GamePlayerController->GetPawn());
}

void UInteractPromptScreen::OnCurrentInteractionCompleted(UInteractionBase* Interaction)
{
	IInteractable::Execute_OnInteractedWith(TargetInteractableReference.TargetInteractable, GamePlayerController->GetPawn());
	IInteractable::Execute_OnInteractionCompleted(TargetInteractableReference.TargetInteractable, GamePlayerController->GetPawn());

	RemoveCurrentInteractionAndProgress();
}

void UInteractPromptScreen::OnCurrentInteractionCanceled(UInteractionBase* Interaction)
{
	IInteractable::Execute_OnInteractionCanceled(TargetInteractableReference.TargetInteractable, GamePlayerController->GetPawn(), CurrentInteraction->GetCompletionPercent());

	RemoveCurrentInteractionAndProgress();
}

void UInteractPromptScreen::OnCurrentInteractionCompletionPercentChanged(UInteractionBase* Interaction)
{
	const float NewCompletionPercent{ CurrentInteraction->GetCompletionPercent() };

	IInteractable::Execute_OnInteractionCompletionPercentChanged(TargetInteractableReference.TargetInteractable,
		GamePlayerController->GetPawn(), NewCompletionPercent);

	SetInteractProgressBarProgress(NewCompletionPercent);
}

void UInteractPromptScreen::BindInteractionEvents(UInteractionBase* Interaction)
{
	OnInteractionStartedDelegateHandle = Interaction->OnInteractionStartedDelegate.AddUObject(this, &UInteractPromptScreen::OnCurrentInteractionStarted);
	OnInteractionCompletedDelegateHandle = Interaction->OnInteractionCompletedDelegate.AddUObject(this, &UInteractPromptScreen::OnCurrentInteractionCompleted);
	OnInteractionCanceledDelegateHandle = Interaction->OnInteractionCanceledDelegate.AddUObject(this, &UInteractPromptScreen::OnCurrentInteractionCanceled);
	OnInteractionCompletionPercentChangedDelegateHandle = Interaction->OnInteractionCompletionPercentChangedDelegate.AddUObject(this, 
		&UInteractPromptScreen::OnCurrentInteractionCompletionPercentChanged);
}

void UInteractPromptScreen::UnBindInteractionEvents(UInteractionBase* Interaction)
{
	Interaction->OnInteractionStartedDelegate.Remove(OnInteractionStartedDelegateHandle);
	OnInteractionStartedDelegateHandle.Reset();

	Interaction->OnInteractionCompletedDelegate.Remove(OnInteractionCompletedDelegateHandle);
	OnInteractionCompletedDelegateHandle.Reset();

	Interaction->OnInteractionCanceledDelegate.Remove(OnInteractionCanceledDelegateHandle);
	OnInteractionCanceledDelegateHandle.Reset();

	Interaction->OnInteractionCompletionPercentChangedDelegate.Remove(OnInteractionCompletionPercentChangedDelegateHandle);
	OnInteractionCompletionPercentChangedDelegateHandle.Reset();
}

void UInteractPromptScreen::SetNewCurrentInteraction(EInteractionType InteractionType)
{
	// Create the correct interaction type object for the target interactable's interaction type and set it as the current interaction
	CurrentInteraction = UProject1GameplayLibrary::CreateInteraction(InteractionType, this);

	// Bind to new interaction delegates
	BindInteractionEvents(CurrentInteraction);
}

void UInteractPromptScreen::ClearCurrentInteraction()
{
	UnBindInteractionEvents(CurrentInteraction);
	CurrentInteraction = nullptr;
}

void UInteractPromptScreen::RemoveCurrentInteractionAndProgress()
{
	ClearCurrentInteraction();
	ClearInteractProgressBarProgress();
}

void UInteractPromptScreen::UpdateUIForNewTargetInteractable(bool ShowInteractProgressBar)
{
	// TODO: Switch input prompt to reresent the key needs to be held instead of just pressed if the interactable's interaction type requires it

	InteractProgressBar->SetVisibility((ShowInteractProgressBar) ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Collapsed);
}

void UInteractPromptScreen::SetInteractProgressBarProgress(float Percent)
{
	InteractProgressBar->SetPercent(Percent);
}

void UInteractPromptScreen::ClearInteractProgressBarProgress()
{
	SetInteractProgressBarProgress(0.0f);
}
