// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleScreenAnyInputPromptScreen.h"
#include "HUDs/Project1HUDBase.h"
#include "Kismet/GameplayStatics.h"
#include "Controllers/PlayerControllers/TitleScreenPlayerController.h"

void UTitleScreenAnyInputPromptScreen::NativeOnPushedToLayerStack()
{
	TitleScreenPlayerController = CastChecked<ATitleScreenPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	Project1HUD = CastChecked<AProject1HUDBase>(TitleScreenPlayerController->GetHUD());

	// Register to events
	PressAnyInputTriggeredDelegateHandle = TitleScreenPlayerController->AnyInputTriggered.AddUObject(this, &UTitleScreenAnyInputPromptScreen::OnPressAnyInputPromptAnyInputTriggered);

	// Add input mapping context
	TitleScreenPlayerController->AddPressAnyInputPromptInputMappingContext();
}

void UTitleScreenAnyInputPromptScreen::NativeOnPoppedFromLayerStack()
{
	// Remove input mapping context
	TitleScreenPlayerController->RemovePressAnyInputPromptInputMappingContext();

	// Unregister from events
	TitleScreenPlayerController->AnyInputTriggered.Remove(PressAnyInputTriggeredDelegateHandle);
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
