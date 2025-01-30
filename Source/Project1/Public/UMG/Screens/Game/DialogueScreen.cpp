// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueScreen.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerControllers/GamePlayerController.h"
#include "InputActionValue.h"
#include "GameModes/GameGameMode.h"
#include "Objects/Dialogue/DialogueManagerBase.h"

void UDialogueScreen::NativeOnPushedToLayerStack()
{
	// Get dialogue manager
	DialogueManager = CastChecked<AGameGameMode>(UGameplayStatics::GetGameMode(this))->GetDialogueManager();

	// Get game player controller
	GamePlayerController = CastChecked<AGamePlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	// Register dialogue screen input events
	ConfirmTriggeredDelegateHandle = GamePlayerController->DialogueScreenConfirmTriggered.AddUObject(this, &UDialogueScreen::OnConfirmTriggered);

	// Display initial dialogue line
	const FText* pInitialLineText{ DialogueManager->GetCurrentPlayingNodeDialogueLineText() };
	if (pInitialLineText)
	{
		SetDialogueLineText(*(DialogueManager->GetCurrentPlayingNodeDialogueLineText()));
	}

	// Add dialogue screen inputs
	GamePlayerController->AddDialogueScreenInputMappingContext();
}

void UDialogueScreen::NativeOnPoppedFromLayerStack()
{
	// Remove dialogue screen input events
	GamePlayerController->DialogueScreenConfirmTriggered.Remove(ConfirmTriggeredDelegateHandle);
	ConfirmTriggeredDelegateHandle.Reset();

	// Remove dialogue screen inputs
	GamePlayerController->RemoveDialogueScreenInputMappingContext();
}

void UDialogueScreen::OnConfirmTriggered(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::White, FString::Printf(TEXT("Dialogue screen confirm: %d"), StaticCast<int32>(Value.Get<bool>())));
}
