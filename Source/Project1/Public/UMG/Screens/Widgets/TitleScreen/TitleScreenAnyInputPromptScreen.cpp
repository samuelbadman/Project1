// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleScreenAnyInputPromptScreen.h"
#include "HUDs/Project1HUDBase.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerControllers/TitleScreenPlayerController.h"

void UTitleScreenAnyInputPromptScreen::NativeOnPushedToLayerStack()
{
	TitleScreenPlayerController = CastChecked<ATitleScreenPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	Project1HUD = CastChecked<AProject1HUDBase>(TitleScreenPlayerController->GetHUD());

	// Register to events
	PressAnyInputTriggeredDelegateHandle = TitleScreenPlayerController->PressAnyInputTriggered.AddUObject(this, &UTitleScreenAnyInputPromptScreen::OnPressAnyInputTriggered);

	// Add input mapping context
	TitleScreenPlayerController->AddPressAnyInputInputMappingContext();
}

void UTitleScreenAnyInputPromptScreen::NativeOnPoppedFromLayerStack()
{
	// Remove input mapping context
	TitleScreenPlayerController->RemovePressAnyInputInputMappingContext();

	// Unregister from events
	TitleScreenPlayerController->PressAnyInputTriggered.Remove(PressAnyInputTriggeredDelegateHandle);
	PressAnyInputTriggeredDelegateHandle.Reset();
}

void UTitleScreenAnyInputPromptScreen::OnPressAnyInputTriggered(const FInputActionValue& Value)
{
	// Only handle input if on top of owning widget layer
	if (CanReceiveInput())
	{
		// Push main menu screen to target widget layer
		Project1HUD->PushContentToPrimaryLayoutWidgetLayer(TitleScreenMainMenuScreenTargetLayerName, TitleScreenMainMenuScreenClass);
	}
}
