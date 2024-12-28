// Fill out your copyright notice in the Description page of Project Settings.


#include "Project1PlayerControllerBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameInstances/Project1GameInstanceBase.h"
#include "ProjectInput/InputKeyStateManager.h"

void AProject1PlayerControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Bind any key pressed, released and repeated event function
	// Pressed
	FInputKeyBinding AnyKeyPressedBinding(EKeys::AnyKey, EInputEvent::IE_Pressed);
	AnyKeyPressedBinding.bConsumeInput = true;
	AnyKeyPressedBinding.bExecuteWhenPaused = true;
	AnyKeyPressedBinding.KeyDelegate.GetDelegateWithKeyForManualSet().BindLambda([&](const FKey& Key)
		{
			OnAnyKeyInput(Key, IE_Pressed);
		}
	);

	// Repeat
	FInputKeyBinding AnyKeyRepeatBinding(EKeys::AnyKey, EInputEvent::IE_Repeat);
	AnyKeyRepeatBinding.bConsumeInput = true;
	AnyKeyRepeatBinding.bExecuteWhenPaused = true;
	AnyKeyRepeatBinding.KeyDelegate.GetDelegateWithKeyForManualSet().BindLambda([&](const FKey& Key)
		{
			OnAnyKeyInput(Key, IE_Repeat);
		}
	);

	// Released
	FInputKeyBinding AnyKeyReleasedBinding(EKeys::AnyKey, EInputEvent::IE_Released);
	AnyKeyReleasedBinding.bConsumeInput = true;
	AnyKeyReleasedBinding.bExecuteWhenPaused = true;
	AnyKeyReleasedBinding.KeyDelegate.GetDelegateWithKeyForManualSet().BindLambda([&](const FKey& Key)
		{
			OnAnyKeyInput(Key, IE_Released);
		}
	);

	InputComponent->KeyBindings.Add(AnyKeyPressedBinding);
	InputComponent->KeyBindings.Add(AnyKeyRepeatBinding);
	InputComponent->KeyBindings.Add(AnyKeyReleasedBinding);
}

void AProject1PlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();

	// Get game instance reference as project game instance to access input key state manager object
	ProjectGameInstance = CastChecked<UProject1GameInstanceBase>(UGameplayStatics::GetPlayerController(this, 0)->GetGameInstance());
}

void AProject1PlayerControllerBase::OnAnyKeyInput(const FKey& Key, const EInputEvent InputEvent)
{
	// Get input key state manager from game instance
	UInputKeyStateManager& InputKeyStateManager{ ProjectGameInstance->GetInputKeyStateManager() };

	// Get new key state for the input key
	const EInputKeyState NewKeyState{ InputKeyStateManager.GetInputKeyStateFromInputEvent(InputEvent) };

	// If the input event was pressed or released, ignore the input if the key is already in the corresponding key state. This prevents incorrect input events being generated
	// when a key is held while opening levels
	if ((InputEvent == EInputEvent::IE_Pressed) ||
		(InputEvent == EInputEvent::IE_Released))
	{
		// If the key is already in the new key state, ignore the input
		if (InputKeyStateManager.GetKeyState(Key) == NewKeyState)
		{
			return;
		}
	}

	// Update input key state
	InputKeyStateManager.SetKeyState(Key, NewKeyState);

	// Handle the input
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Cyan, FString::Printf(TEXT("AnyKeyInput: Key %s, InputEvent %s"),
		*Key.GetDisplayName().ToString(), *UEnum::GetDisplayValueAsText(InputEvent).ToString()));
}
