// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleScreenPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "GameViewportClients/Project1GameViewportClientBase.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

void ATitleScreenPlayerController::AddPressAnyInputInputMappingContext()
{
	const TObjectPtr<UEnhancedInputLocalPlayerSubsystem> EnhancedInputLocalPlayerSubsystem = GetEnhancedInputLocalPlayerSubsystem();
	EnhancedInputLocalPlayerSubsystem->AddMappingContext(PressAnyInputInputMappingContext, PressAnyInputMappingContextPriority);
}

void ATitleScreenPlayerController::RemovePressAnyInputInputMappingContext()
{
	const TObjectPtr<UEnhancedInputLocalPlayerSubsystem> EnhancedInputLocalPlayerSubsystem = GetEnhancedInputLocalPlayerSubsystem();
	EnhancedInputLocalPlayerSubsystem->RemoveMappingContext(PressAnyInputInputMappingContext);
}

void ATitleScreenPlayerController::AddMainMenuUIInputMappingContext()
{
	const TObjectPtr<UEnhancedInputLocalPlayerSubsystem> EnhancedInputLocalPlayerSubsystem = GetEnhancedInputLocalPlayerSubsystem();
	EnhancedInputLocalPlayerSubsystem->AddMappingContext(MainMenuUIInputMappingContext, MainMenuUIInputMappingContextPriority);
}

void ATitleScreenPlayerController::RemoveMainMenuUIInputMappingContext()
{
	const TObjectPtr<UEnhancedInputLocalPlayerSubsystem> EnhancedInputLocalPlayerSubsystem = GetEnhancedInputLocalPlayerSubsystem();
	EnhancedInputLocalPlayerSubsystem->RemoveMappingContext(MainMenuUIInputMappingContext);
}

void ATitleScreenPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	const TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent{ CastChecked<UEnhancedInputComponent>(InputComponent) };

	EnhancedInputComponent->BindAction(PressAnyInputInputAction, ETriggerEvent::Triggered, this, &ATitleScreenPlayerController::OnPressAnyInputTriggered);

	EnhancedInputComponent->BindAction(MainMenuUIConfirmInputAction, ETriggerEvent::Triggered, this, &ATitleScreenPlayerController::OnMainMenuUIConfirmTriggered);
	EnhancedInputComponent->BindAction(MainMenuUINavigateInputAction, ETriggerEvent::Triggered, this, &ATitleScreenPlayerController::OnMainMenuUINavigateTriggered);
}

void ATitleScreenPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Get project1 game viewport client
	Project1GameViewportClient = CastChecked<UProject1GameViewportClientBase>(UGameplayStatics::GetGameInstance(this)->GetGameViewportClient());

	// Bind to on input device changed events
	OnMouseMovedDelegateHandle = Project1GameViewportClient->MouseMoved.AddWeakLambda(this,
		[this](const FVector2D& NewMousePosition, const FVector2D& OldMousePosition, const FVector2D& MouseMoveDelta) {
			SetMouseCursorVisibility(EMouseCursorVisibility::Visible, bLockMouseToViewportWhenShown, bCenterMouseInViewportWhenShown);
		});

	OnInputKeyDelegateHandle = Project1GameViewportClient->OnInputKey.AddWeakLambda(this,
		[this](const FInputKeyEventArgs& EventArgs) {
			EMouseCursorVisibility NewCursorVisibility{ ((EventArgs.Key == EKeys::LeftMouseButton) ||
				(EventArgs.Key == EKeys::MiddleMouseButton) ||
				(EventArgs.Key == EKeys::RightMouseButton) ||
				(EventArgs.Key == EKeys::MouseScrollUp) ||
				(EventArgs.Key == EKeys::MouseScrollDown)) ? EMouseCursorVisibility::Visible : EMouseCursorVisibility::Hidden };

			SetMouseCursorVisibility(NewCursorVisibility, bLockMouseToViewportWhenShown, bCenterMouseInViewportWhenShown);
		});
}

void ATitleScreenPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	// Unbind from game viewport client events
	Project1GameViewportClient->MouseMoved.Remove(OnMouseMovedDelegateHandle);
	OnMouseMovedDelegateHandle.Reset();

	Project1GameViewportClient->OnInputKey.Remove(OnInputKeyDelegateHandle);
	OnInputKeyDelegateHandle.Reset();
}

void ATitleScreenPlayerController::OnPressAnyInputTriggered(const FInputActionValue& Value)
{
	PressAnyInputTriggered.Broadcast(Value);
}

void ATitleScreenPlayerController::OnMainMenuUIConfirmTriggered(const FInputActionValue& Value)
{
	MainMenuUIConfirmTriggered.Broadcast(Value);
}

void ATitleScreenPlayerController::OnMainMenuUINavigateTriggered(const FInputActionValue& Value)
{
	MainMenuUINavigateTriggered.Broadcast(Value);
}
