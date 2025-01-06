// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleScreenAnyInputPromptScreen.h"
#include "HUDs/Project1HUDBase.h"
#include "Kismet/GameplayStatics.h"
#include "InputActionValue.h"

void UTitleScreenAnyInputPromptScreen::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Project1HUD = CastChecked<AProject1HUDBase>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
}

void UTitleScreenAnyInputPromptScreen::NativeOnShown()
{
	// TODO: Play animation to fade in UI
}

void UTitleScreenAnyInputPromptScreen::NativeOnAnyInputTriggered(const FInputActionValue& Value)
{
	Project1HUD->PushContentToPrimaryLayoutLayer(TitleScreenMainMenuScreenTargetLayerName, TitleScreenMainMenuScreenClass);
}
