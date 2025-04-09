// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueScreen.h"
#include "Kismet/GameplayStatics.h"
#include "Controllers/PlayerControllers/GamePlayerController.h"
#include "InputActionValue.h"
#include "GameModes/GameGameMode.h"
#include "Objects/Dialogue/DialogueManagerBase.h"
#include "Objects/ScreenLoadPayloads/DialogueScreenLoadPayload.h"
#include "Objects/Dialogue/DialogueNode.h"
#include "UMG/Components/ScrollingTextBlock.h"

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
	//const TObjectPtr<UDialogueScreenLoadPayload> Payload{ CastChecked<UDialogueScreenLoadPayload>(LoadPayload) };
}

void UDialogueScreen::OnConfirmTriggered(const FInputActionValue& Value)
{
	const TObjectPtr<UScrollingTextBlock> ScrollingTextBlock{ GetScrollingTextBlock() };
	if (ScrollingTextBlock->IsScrolling())
	{
		GetScrollingTextBlock()->StopScroll(true);
	}
	else
	{
		DialogueManager->ProgressDialogue();
	}
}

void UDialogueScreen::OnDialogueNodePlayed(const TObjectPtr<UDialogueNode> DialogueNode)
{
	const TObjectPtr<UScrollingTextBlock> ScrollingTextBlock{ GetScrollingTextBlock() };
	ScrollingTextBlock->SetText(DialogueNode->GetDialogueLine());
	ScrollingTextBlock->BeginScroll();
}
