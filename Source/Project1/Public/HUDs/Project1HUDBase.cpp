// Fill out your copyright notice in the Description page of Project Settings.


#include "Project1HUDBase.h"
#include "UserWidgets/PrimaryLayouts/PrimaryLayoutUserWidgetBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameInstances/Project1GameInstanceBase.h"
#include "ProjectInput/InputKeyStateController.h"

void AProject1HUDBase::PushContentToPrimaryLayoutLayer(const FGameplayTag& LayerName, const TSoftClassPtr<UScreenUserWidgetBase>& WidgetClass)
{
	PrimaryLayoutWidget->PushContentToLayer(LayerName, WidgetClass);
}

void AProject1HUDBase::PopContentFromPrimaryLayoutLayer(const FGameplayTag& LayerName)
{
	PrimaryLayoutWidget->PopContentFromLayer(LayerName);
}

ULayerUserWidgetBase* AProject1HUDBase::GetRegisteredPrimaryLayoutLayer(const FGameplayTag& LayerName)
{
	return PrimaryLayoutWidget->GetRegisteredLayer(LayerName);
}

void AProject1HUDBase::SetActiveInputPrimaryLayoutLayer(const FGameplayTag& LayerName)
{
	PrimaryLayoutWidget->SetActiveInputLayer(LayerName);
}

const FGameplayTag& AProject1HUDBase::GetActiveInputPrimaryLayoutLayerName() const
{
	return PrimaryLayoutWidget->GetActiveInputLayerName();
}

bool AProject1HUDBase::IsContentOnTopOfPrimaryLayoutLayer(const FGameplayTag& LayerName, TObjectPtr<UScreenUserWidgetBase> Widget) const
{
	return PrimaryLayoutWidget->IsContentOnTopOfLayer(LayerName, Widget);
}

void AProject1HUDBase::BeginPlay()
{
	Super::BeginPlay();

	// Get references
	Project1GameInstance = Cast<UProject1GameInstanceBase>(UGameplayStatics::GetGameInstance(this));

	// Create primary layout widget, cache it and add it to the viewport
	PrimaryLayoutWidget = CreateWidget<UPrimaryLayoutUserWidgetBase>(GetOwningPlayerController(), PrimaryLayoutWidgetClass);
#if WITH_EDITOR
	if (!IsValid(PrimaryLayoutWidget))
	{
		UE_LOG(LogTemp, Error, TEXT("PrimaryLayoutWidget failed to create. Is a class set in the HUD blueprint?"));
		return;
	}
#endif
	PrimaryLayoutWidget->AddToViewport();

	// Bind to player controller input key events to rout to UI inputs
	FInputKeyBinding AnyKeyPressedBinding(FInputChord(EKeys::AnyKey), EInputEvent::IE_Pressed);
	AnyKeyPressedBinding.bConsumeInput = false;
	AnyKeyPressedBinding.bExecuteWhenPaused = true;
	AnyKeyPressedBinding.KeyDelegate.GetDelegateWithKeyForManualSet().BindLambda([this](const FKey& Key)
		{
			ControllerAnyKeyInputBinding(Key, IE_Pressed);
		});

	FInputKeyBinding AnyKeyReleasedBinding(FInputChord(EKeys::AnyKey), EInputEvent::IE_Released);
	AnyKeyReleasedBinding.bConsumeInput = false;
	AnyKeyReleasedBinding.bExecuteWhenPaused = true;
	AnyKeyReleasedBinding.KeyDelegate.GetDelegateWithKeyForManualSet().BindLambda([this](const FKey& Key)
		{
			ControllerAnyKeyInputBinding(Key, IE_Released);
		});

	FInputKeyBinding AnyKeyRepeatBinding(FInputChord(EKeys::AnyKey), EInputEvent::IE_Repeat);
	AnyKeyRepeatBinding.bConsumeInput = false;
	AnyKeyRepeatBinding.bExecuteWhenPaused = true;
	AnyKeyRepeatBinding.KeyDelegate.GetDelegateWithKeyForManualSet().BindLambda([this](const FKey& Key)
		{
			ControllerAnyKeyInputBinding(Key, IE_Repeat);
		});

	const TObjectPtr<APlayerController> PlayerController{ UGameplayStatics::GetPlayerController(this, 0) };
	PlayerController->InputComponent->KeyBindings.Add(AnyKeyPressedBinding);
	PlayerController->InputComponent->KeyBindings.Add(AnyKeyReleasedBinding);
	PlayerController->InputComponent->KeyBindings.Add(AnyKeyRepeatBinding);
}

void AProject1HUDBase::ControllerAnyKeyInputBinding(const FKey& Key, const EInputEvent Event)
{
	// Get input key state controller
	UInputKeyStateController& InputKeyStateController{ Project1GameInstance->GetInputKeyStateController() };

	// Get new key state for the input key
	const EInputKeyState NewKeyState{ InputKeyStateController.GetInputKeyStateFromInputEvent(Event) };

	// If the input was pressed or released and the key is already in the new key state, ignore the input. This prevents held keys when opening a new level from triggering inaccurate 
	// pressed events
	if ((Event == IE_Pressed) ||
		(Event == IE_Released))
	{
		if (InputKeyStateController.GetKeyState(Key) == NewKeyState)
		{
			return;
		}
	}

	// Update input key state
	InputKeyStateController.SetKeyState(Key, NewKeyState);

	// Route input to primary layout widget's active input layer
	PrimaryLayoutWidget->RouteInputToActiveInputLayer(Key, Event);
}
