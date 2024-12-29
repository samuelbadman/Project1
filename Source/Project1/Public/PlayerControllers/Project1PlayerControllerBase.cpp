// Fill out your copyright notice in the Description page of Project Settings.


#include "Project1PlayerControllerBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameInstances/Project1GameInstanceBase.h"
#include "ProjectInput/InputKeyStateController.h"
#include "Kismet/KismetSystemLibrary.h"

void AProject1PlayerControllerBase::SetMouseCursorVisibility(EMouseCursorVisibility NewVisibility, bool LockMouseCursorToViewportWhenVisible, bool CenterCursorInViewportOnBecomeVisible)
{
	FInputModeGameAndUI InputModeGameAndUI{};
	InputModeGameAndUI.SetHideCursorDuringCapture(false);

	switch (NewVisibility)
	{
	case EMouseCursorVisibility::Visible:
		InputModeGameAndUI.SetLockMouseToViewportBehavior((LockMouseCursorToViewportWhenVisible) ? EMouseLockMode::LockAlways : EMouseLockMode::DoNotLock);

		SetShowMouseCursor(true);

		if (CenterCursorInViewportOnBecomeVisible)
		{
			int32 ViewportX{ 0 }, ViewportY{ 0 };
			GetViewportSize(ViewportX, ViewportY);
			SetMouseLocation(ViewportX / 2, ViewportY / 2);
		}

		break;

	case EMouseCursorVisibility::Hidden:
		InputModeGameAndUI.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);

		SetShowMouseCursor(false);

		break;
	}

	SetInputMode(InputModeGameAndUI);

	FSlateApplication::Get().QueryCursor();
}

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
	ProjectGameInstance = CastChecked<UProject1GameInstanceBase>(UGameplayStatics::GetGameInstance(this));

	// Set default mouse cursor visibility
	SetMouseCursorVisibility(DefaultMouseCursorVisibility, DefaultLockMouseCursorToViewportWhenVisible, DefaultCenterCursorInViewportOnBecomeVisible);
}

void AProject1PlayerControllerBase::OnAnyKeyInput(const FKey& Key, EInputEvent InputEvent)
{
	// Get input key state manager from game instance
	UInputKeyStateController& InputKeyStateController{ ProjectGameInstance->GetInputKeyStateController() };

	// Get new key state for the input key
	const EInputKeyState NewKeyState{ InputKeyStateController.GetInputKeyStateFromInputEvent(InputEvent) };

	// Ignore the input if the key is already in the corresponding key state. This prevents incorrect input events being generated when a key is held while opening levels
	if ((InputEvent == EInputEvent::IE_Pressed) ||
		(InputEvent == EInputEvent::IE_Released))
	{
		// If the key is already in the new key state, ignore the input
		if (InputKeyStateController.GetKeyState(Key) == NewKeyState)
		{
			return;
		}
	}

	// Update input key state
	InputKeyStateController.SetKeyState(Key, NewKeyState);

	// Handle the input
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Cyan, FString::Printf(TEXT("%s AnyKeyInput: Key %s, InputEvent %s"),
		*UKismetSystemLibrary::GetDisplayName(this), *Key.GetDisplayName().ToString(), *UEnum::GetDisplayValueAsText(InputEvent).ToString()));

	ReceiveAnyKeyInput(Key, InputEvent);
}

bool AProject1PlayerControllerBase::IsMouseCursorVisible() const
{
	return bShowMouseCursor;
}
