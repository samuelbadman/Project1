// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueScreen.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerControllers/GamePlayerController.h"
#include "InputActionValue.h"
#include "GameModes/GameGameMode.h"
#include "Objects/Dialogue/DialogueManagerBase.h"
#include "Objects/ScreenLoadPayloads/DialogueScreenLoadPayload.h"
#include "Objects/Dialogue/DialogueNode.h"

void UDialogueScreen::NativeOnPushedToLayerStack()
{
	// Get world
	World = GetWorld();

	// Get dialogue manager
	DialogueManager = CastChecked<AGameGameMode>(UGameplayStatics::GetGameMode(this))->GetDialogueManager();

	// Get game player controller
	GamePlayerController = CastChecked<AGamePlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	// Register dialogue screen input events
	ConfirmTriggeredDelegateHandle = GamePlayerController->DialogueScreenConfirmTriggered.AddUObject(this, &UDialogueScreen::OnConfirmTriggered);

	// Register dialogue manager events
	DialogueNodePlayedDelegateHandle = DialogueManager->OnPlayedDialogueNode.AddUObject(this, &UDialogueScreen::OnDialogueNodePlayed);

	// Add dialogue screen inputs
	GamePlayerController->AddDialogueScreenInputMappingContext();
}

void UDialogueScreen::NativeOnPoppedFromLayerStack()
{
	// Remove dialogue screen input events
	GamePlayerController->DialogueScreenConfirmTriggered.Remove(ConfirmTriggeredDelegateHandle);
	ConfirmTriggeredDelegateHandle.Reset();

	// Remove dialogue manager events
	DialogueManager->OnPlayedDialogueNode.Remove(DialogueNodePlayedDelegateHandle);
	DialogueNodePlayedDelegateHandle.Reset();

	// Remove dialogue screen inputs
	GamePlayerController->RemoveDialogueScreenInputMappingContext();
}

void UDialogueScreen::NativeConsumeLoadPayload(TObjectPtr<UScreenWidgetLoadPayloadBase> LoadPayload)
{
	const TObjectPtr<UDialogueScreenLoadPayload> Payload{ CastChecked<UDialogueScreenLoadPayload>(LoadPayload) };

	// Set initial dialogue line
	SetDialogueLineText(Payload->InitialDialogueLineText);
}

void UDialogueScreen::OnConfirmTriggered(const FInputActionValue& Value)
{
	DialogueManager->ProgressDialogue();
}

void UDialogueScreen::OnDialogueNodePlayed(const TObjectPtr<UDialogueNode> DialogueNode)
{
	ScrolledDialogueLineString.Empty();
	PlayingDialogueLineStringCharIndex = 0;
	PlayingDialogueLineString = DialogueNode->GetDialogueLine().ToString();
	SetDialogueLineText(FText::FromString(TEXT("")));

	World->GetTimerManager().SetTimer(DialogueLineScrollTimerHandle, this, &UDialogueScreen::IncrementDialogueLineScroll, DialogueLineScrollRate, true);
}

void UDialogueScreen::IncrementDialogueLineScroll()
{
	ScrolledDialogueLineString += PlayingDialogueLineString[PlayingDialogueLineStringCharIndex++];
	SetDialogueLineText(FText::FromString(ScrolledDialogueLineString));

	if (!PlayingDialogueLineString.IsValidIndex(PlayingDialogueLineStringCharIndex))
	{
		World->GetTimerManager().ClearTimer(DialogueLineScrollTimerHandle);
	}
}
