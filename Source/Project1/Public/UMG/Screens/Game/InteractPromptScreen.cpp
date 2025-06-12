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

void UInteractPromptScreen::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, FString::Printf(TEXT("Interact prompt tick")));
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

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::White, FString::Printf(TEXT("Target interactable changed")));

	// Update interact prompt UI for new target interactable
	UpdateUIForNewTargetInteractable(false);

	// Update the interact action text in the interact prompt UI
	SetInteractActionText(FText::FromString(TEXT("")));
}

void UInteractPromptScreen::OnInteractStarted(const FInputActionValue& Value)
{
	// Only want to handle inputs when the widget is on top of the owning layer
	if (!CanReceiveInput())
	{
		return;
	}

	// The interact input has been pressed
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::White, FString::Printf(TEXT("Interact input pressed")));
}

void UInteractPromptScreen::OnInteractTriggered(const FInputActionValue& Value)
{
	// Only want to handle inputs when the widget is on top of the owning layer
	if (!CanReceiveInput())
	{
		return;
	}

	// The interact input is being held down
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::White, FString::Printf(TEXT("Interact input held down")));
}

void UInteractPromptScreen::OnInteractCompleted(const FInputActionValue& Value)
{
	// Only want to handle inputs when the widget is on top of the owning layer
	if (!CanReceiveInput())
	{
		return;
	}

	// The interact input has been released
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::White, FString::Printf(TEXT("Interact input released")));
}

void UInteractPromptScreen::OnSwitchActionTriggered(const FInputActionValue& Value)
{
	// Only want to handle inputs when the widget is on top of the owning layer
	if (!CanReceiveInput())
	{
		return;
	}

	// Cannot switch interact actions when in an interaction


	// Switch interact action
	if (PlayerInteractComponent->GetNumOverlappedInteractables() > 1)
	{
		PlayerInteractComponent->IncrementTargetInteractableIndex(StaticCast<int32>(Value.Get<float>()));
	}
}

void UInteractPromptScreen::UpdateUIForNewTargetInteractable(bool ShowInteractProgressBar)
{
	// TODO: Switch input prompt to reresent the key needs to be held instead of just pressed if the interactable's interaction type requires it

	InteractProgressBar->SetVisibility((ShowInteractProgressBar) ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Collapsed);
}

void UInteractPromptScreen::ClearInteractProgressBarProgress()
{
	InteractProgressBar->SetPercent(0.0f);
}
