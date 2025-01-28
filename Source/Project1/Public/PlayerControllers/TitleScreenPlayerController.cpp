// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleScreenPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "GameViewportClients/Project1GameViewportClientBase.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "DataAssets/InputMapping/PressAnyInputPromptInputMapping.h"
#include "DataAssets/InputMapping/MainMenuScreenInputMapping.h"

void ATitleScreenPlayerController::AddPressAnyInputPromptInputMappingContext()
{
	const TObjectPtr<UEnhancedInputLocalPlayerSubsystem> EnhancedInputLocalPlayerSubsystem = GetEnhancedInputLocalPlayerSubsystem();
	EnhancedInputLocalPlayerSubsystem->AddMappingContext(PressAnyInputPromptInputMapping->GetInputMappingContext(), PressAnyInputPromptInputPriority);
}

void ATitleScreenPlayerController::RemovePressAnyInputPromptInputMappingContext()
{
	const TObjectPtr<UEnhancedInputLocalPlayerSubsystem> EnhancedInputLocalPlayerSubsystem = GetEnhancedInputLocalPlayerSubsystem();
	EnhancedInputLocalPlayerSubsystem->RemoveMappingContext(PressAnyInputPromptInputMapping->GetInputMappingContext());
}

void ATitleScreenPlayerController::AddMainMenuScreenInputMappingContext()
{
	const TObjectPtr<UEnhancedInputLocalPlayerSubsystem> EnhancedInputLocalPlayerSubsystem = GetEnhancedInputLocalPlayerSubsystem();
	EnhancedInputLocalPlayerSubsystem->AddMappingContext(MainMenuScreenInputMapping->GetInputMappingContext(), MainMenuScreenInputPriority);
}

void ATitleScreenPlayerController::RemoveMainMenuScreenInputMappingContext()
{
	const TObjectPtr<UEnhancedInputLocalPlayerSubsystem> EnhancedInputLocalPlayerSubsystem = GetEnhancedInputLocalPlayerSubsystem();
	EnhancedInputLocalPlayerSubsystem->RemoveMappingContext(MainMenuScreenInputMapping->GetInputMappingContext());
}

void ATitleScreenPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	const TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent{ CastChecked<UEnhancedInputComponent>(InputComponent) };

	EnhancedInputComponent->BindAction(PressAnyInputPromptInputMapping->GetAnyInputInputAction(), ETriggerEvent::Triggered, 
		this, &ATitleScreenPlayerController::OnPressAnyInputPromptAnyInputTriggered);

	EnhancedInputComponent->BindAction(MainMenuScreenInputMapping->GetConfirmInputAction(), ETriggerEvent::Triggered, 
		this, &ATitleScreenPlayerController::OnMainMenuScreenConfirmTriggered);
	EnhancedInputComponent->BindAction(MainMenuScreenInputMapping->GetNavigateInputAction(), ETriggerEvent::Triggered, 
		this, &ATitleScreenPlayerController::OnMainMenuScreenNavigateTriggered);
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

void ATitleScreenPlayerController::OnPressAnyInputPromptAnyInputTriggered(const FInputActionValue& Value)
{
	AnyInputTriggered.Broadcast(Value);
}

void ATitleScreenPlayerController::OnMainMenuScreenConfirmTriggered(const FInputActionValue& Value)
{
	MainMenuScreenConfirmTriggered.Broadcast(Value);
}

void ATitleScreenPlayerController::OnMainMenuScreenNavigateTriggered(const FInputActionValue& Value)
{
	MainMenuScreenNavigateTriggered.Broadcast(Value);
}
