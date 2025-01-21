// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleScreenPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "GameViewportClients/Project1GameViewportClientBase.h"
#include "HUDs/Project1HUDBase.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "DataAssets/UIInputMapping.h"

void ATitleScreenPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Get project1 game viewport client
	Project1GameViewportClient = CastChecked<UProject1GameViewportClientBase>(UGameplayStatics::GetGameInstance(this)->GetGameViewportClient());

	// Bind to on input device changed events
	Project1GameViewportClient->GetOnInputDeviceChangedDelegate().AddWeakLambda(this,
		[this](bool UsingGamepad) {
			SetMouseCursorVisibility((UsingGamepad) ? EMouseCursorVisibility::Hidden : EMouseCursorVisibility::Visible, bLockMouseToViewportWhenShown, bCenterMouseInViewportWhenShown);
		});

	// Setup UI inputs
	Project1HUD = CastChecked<AProject1HUDBase>(GetHUD());
	Project1HUD->BindUIInputActions(CastChecked<UEnhancedInputComponent>(InputComponent));
	Project1HUD->BindToMouseMoveEvents(Project1GameViewportClient);

	const TObjectPtr<UEnhancedInputLocalPlayerSubsystem> EnhancedInputLocalPlayerSubsystem{ GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>() };
	const TObjectPtr<UUIInputMapping> UIInputMapping{ Project1HUD->GetUIInputMapping() };
	EnhancedInputLocalPlayerSubsystem->AddMappingContext(UIInputMapping->GetUIMouseInputMappingContext(), UIInputMapping->GetUIMouseInputMappingContextPriority());
	EnhancedInputLocalPlayerSubsystem->AddMappingContext(UIInputMapping->GetUINavigateInputMappingContext(), UIInputMapping->GetUINavigateInputMappingContextPriority());
	EnhancedInputLocalPlayerSubsystem->AddMappingContext(UIInputMapping->GetUIConfirmInputMappingContext(), UIInputMapping->GetUIConfirmInputMappingContextPriority());
	EnhancedInputLocalPlayerSubsystem->AddMappingContext(UIInputMapping->GetUICancelInputMappingContext(), UIInputMapping->GetUICancelInputMappingContextPriority());
	EnhancedInputLocalPlayerSubsystem->AddMappingContext(UIInputMapping->GetUITabInputMappingContext(), UIInputMapping->GetUITabInputMappingContextPriority());
	EnhancedInputLocalPlayerSubsystem->AddMappingContext(UIInputMapping->GetUIAnyInputInputMappingContext(), UIInputMapping->GetUIAnyInputInputMappingContextPriority());
}

void ATitleScreenPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	// Unbind from game viewport client events
	Project1GameViewportClient->GetOnInputDeviceChangedDelegate().Clear();
	Project1HUD->UnbindFromMouseMoveEvents(Project1GameViewportClient);
}
