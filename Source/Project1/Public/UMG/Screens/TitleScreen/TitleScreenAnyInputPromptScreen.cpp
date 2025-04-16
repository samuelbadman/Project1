// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleScreenAnyInputPromptScreen.h"
#include "HUDs/Project1HUDBase.h"
#include "Kismet/GameplayStatics.h"
#include "Controllers/PlayerControllers/Project1PlayerControllerBase.h"
#include "Components/ActorComponents/UIInputComponent.h"
#include "Objects/UIInput/Inputs/PressAnyInputScreenUIInput.h"

void UTitleScreenAnyInputPromptScreen::NativeOnPushedToLayerStack()
{
	Project1PlayerController = CastChecked<AProject1PlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));
	Project1HUD = CastChecked<AProject1HUDBase>(Project1PlayerController->GetHUD());
	PressAnyInputScreenUIInput = Project1PlayerController->GetUIInputComponent()->GetUIInputAs<UPressAnyInputScreenUIInput>(UIInputKey);

	// Register to events
	PressAnyInputTriggeredDelegateHandle = PressAnyInputScreenUIInput->AnyInputTriggered.AddUObject(this, &UTitleScreenAnyInputPromptScreen::OnPressAnyInputPromptAnyInputTriggered);

	// Add input mapping context
	PressAnyInputScreenUIInput->Add(Project1PlayerController->GetEnhancedInputLocalPlayerSubsystem());
}

void UTitleScreenAnyInputPromptScreen::NativeOnPoppedFromLayerStack()
{
	// Remove input mapping context
	PressAnyInputScreenUIInput->Remove(Project1PlayerController->GetEnhancedInputLocalPlayerSubsystem());

	// Unregister from events
	PressAnyInputScreenUIInput->AnyInputTriggered.Remove(PressAnyInputTriggeredDelegateHandle);
	PressAnyInputTriggeredDelegateHandle.Reset();
}

void UTitleScreenAnyInputPromptScreen::OnPressAnyInputPromptAnyInputTriggered(const FInputActionValue& Value)
{
	// Only handle input if on top of owning widget layer
	if (CanReceiveInput())
	{
		// Push main menu screen to target widget layer
		Project1HUD->PushContentToPrimaryLayoutWidgetLayer(TitleScreenMainMenuScreenTargetLayerName, TitleScreenMainMenuScreenClass);
	}
}
