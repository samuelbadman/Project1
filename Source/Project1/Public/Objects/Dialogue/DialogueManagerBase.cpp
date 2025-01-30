// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueManagerBase.h"
#include "Objects/Dialogue/DialogueNode.h"
#include "UMG/Screens/Game/DialogueScreen.h"
#include "HUDs/Project1HUDBase.h"
#include "Kismet/GameplayStatics.h"
#include "Objects/ScreenLoadPayloads/DialogueScreenLoadPayload.h"

void UDialogueManagerBase::BeginPlay()
{
	Project1HUD = CastChecked<AProject1HUDBase>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
}

void UDialogueManagerBase::BeginDialogueBranch(TObjectPtr<UDialogueNode> BranchRootNode, TObjectPtr<UDialogueComponent> Component)
{
	// TODO: Reject dialogue branch if dialogue is currently playing

	ComponentPlayingDialogue = Component;
	PlayDialogueNode(BranchRootNode);

	// Push dialogue screen widget to widget layer
	const TObjectPtr<UDialogueScreenLoadPayload> DialogueScreenLoadPayload{ NewObject<UDialogueScreenLoadPayload>() };
	DialogueScreenLoadPayload->InitialDialogueLineText = BranchRootNode->GetDialogueLine();

	Project1HUD->PushContentToPrimaryLayoutWidgetLayer(DialogueScreenWidgetLayerName, DialogueScreenWidgetClass, DialogueScreenLoadPayload);
}

void UDialogueManagerBase::ProgressDialogue()
{
	// Finish the current playing node
	CurrentPlayingNode->OnFinished(ComponentPlayingDialogue);

	// Does the current playing node have a next one
	const TObjectPtr<UDialogueNode> NextNode{ CurrentPlayingNode->GetNextDialogueNode() };
	if (IsValid(NextNode))
	{
		PlayDialogueNode(NextNode);
	}
	else
	{
		// Reached the end of the dialogue branch
		Project1HUD->PopContentFromPrimaryLayoutWidgetLayer(DialogueScreenWidgetLayerName);

		ComponentPlayingDialogue = nullptr;
		CurrentPlayingNode = nullptr;
	}
}

void UDialogueManagerBase::PlayDialogueNode(TObjectPtr<UDialogueNode> Node)
{
	CurrentPlayingNode = Node;
	Node->OnPlayed(ComponentPlayingDialogue);
	OnPlayedDialogueNode.Broadcast(Node);
}
