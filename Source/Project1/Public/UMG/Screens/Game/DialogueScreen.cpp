// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueScreen.h"
#include "Kismet/GameplayStatics.h"
#include "Controllers/PlayerControllers/Project1PlayerControllerBase.h"
#include "InputActionValue.h"
#include "GameModes/GameGameMode.h"
#include "Objects/Dialogue/DialogueManagerBase.h"
#include "Objects/ScreenLoadPayloads/DialogueScreenLoadPayload.h"
#include "Objects/Dialogue/DialogueNode.h"
#include "UMG/Components/ScrollingTextBlock.h"
#include "Components/ActorComponents/UIInputComponent.h"
#include "Objects/UIInput/Inputs/DialogueScreenUIInput.h"

void UDialogueScreen::NativeOnPushedToLayerStack()
{
	// Get world
	World = GetWorld();

	// Get dialogue manager
	DialogueManager = CastChecked<AGameGameMode>(UGameplayStatics::GetGameMode(this))->GetDialogueManager();

	// Get game player controller
	PlayerController = CastChecked<AProject1PlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));

	// Get dialogue screen UI input
	DialogueScreenUIInput = PlayerController->GetUIInputComponent()->GetUIInputAs<UDialogueScreenUIInput>(UIInputKey);

	// Register dialogue screen input events
	ConfirmTriggeredDelegateHandle = DialogueScreenUIInput->ConfirmTriggered.AddUObject(this, &UDialogueScreen::OnConfirmTriggered);

	// Register dialogue manager events
	DialogueNodePlayedDelegateHandle = DialogueManager->OnPlayedDialogueNode.AddUObject(this, &UDialogueScreen::OnDialogueNodePlayed);

	// Add dialogue screen inputs
	DialogueScreenUIInput->Add(PlayerController->GetEnhancedInputLocalPlayerSubsystem());
}

void UDialogueScreen::NativeOnPoppedFromLayerStack()
{
	// Remove dialogue screen input events
	DialogueScreenUIInput->ConfirmTriggered.Remove(ConfirmTriggeredDelegateHandle);
	ConfirmTriggeredDelegateHandle.Reset();

	// Remove dialogue manager events
	DialogueManager->OnPlayedDialogueNode.Remove(DialogueNodePlayedDelegateHandle);
	DialogueNodePlayedDelegateHandle.Reset();

	// Remove dialogue screen inputs
	DialogueScreenUIInput->Remove(PlayerController->GetEnhancedInputLocalPlayerSubsystem());
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
