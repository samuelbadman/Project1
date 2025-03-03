// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueManagerBase.h"
#include "Objects/Dialogue/DialogueNode.h"
#include "UMG/Screens/Game/DialogueScreen.h"
#include "HUDs/Project1HUDBase.h"
#include "Kismet/GameplayStatics.h"
#include "Objects/ScreenLoadPayloads/DialogueScreenLoadPayload.h"
#include "Objects/ScreenLoadPayloads/DynamicModalScreenLoadPayload.h"
#include "Components/ActorComponents/DialogueComponent.h"
#include "UMG/Screens/Shared/Modals/DynamicModalScreen.h"

void UDialogueManagerBase::BeginPlay()
{
	Project1HUD = CastChecked<AProject1HUDBase>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
}

void UDialogueManagerBase::Tick(float DeltaSeconds)
{
	if (IsPlayingDialogueNode())
	{
		CurrentPlayingNode->Tick(DeltaSeconds, ComponentPlayingDialogue);
	}
}

void UDialogueManagerBase::BeginDialogueBranch(const FGameplayTag& BranchName, TObjectPtr<UDialogueComponent> Component)
{
	// TODO: Reject dialogue branch if dialogue is currently playing
	const TObjectPtr<UDialogueNode> RootNode{ Component->GetDialogueTree()[BranchName] };

	ComponentPlayingDialogue = Component;
	PlayingBranchName = BranchName;
	PlayDialogueNode(RootNode);

	// Push dialogue screen widget to widget layer
	const TObjectPtr<UDialogueScreenLoadPayload> DialogueScreenLoadPayload{ NewObject<UDialogueScreenLoadPayload>() };
	DialogueScreenLoadPayload->InitialDialogueLineText = RootNode->GetDialogueLine();

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
		return;
	}

	// Reached the end of the dialogue branch
	// If the node has dialogue options, show the options in a dynamic modal screen
	if (CurrentPlayingNode->DefinesDialogueOptions())
	{
		const TArray<FDialogueOption>& DialogueOptions{ CurrentPlayingNode->GetDialogueOptions() };
		TArray<FDynamicModalOptionData> ModalOptions{};
		ModalOptions.Reserve(DialogueOptions.Num());

		for (const FDialogueOption& DialogueOption : DialogueOptions)
		{
			FDynamicModalOptionData ModalData{};
			ModalData.OptionText = DialogueOption.OptionButtonText;
			ModalData.OptionSelectedDelegate.BindUFunction(ComponentPlayingDialogue->GetOwner(), DialogueOption.CallbackUFunctionName);

			ModalOptions.Add(ModalData);
		}

		Project1HUD->PushDynamicModalToWidgetLayer(ModalWidgetLayerName, DynamicModalWidgetClass, CurrentPlayingNode->GetDialogueOptionModalPromptText(), ModalOptions);
	}

	// Remove dialogue screen
	Project1HUD->PopContentFromPrimaryLayoutWidgetLayer(DialogueScreenWidgetLayerName);

	// Notify playing component a branch has finished playing
	ComponentPlayingDialogue->NotifyDialogueBranchCompleted(PlayingBranchName);

	// Reset current playing variables
	ComponentPlayingDialogue = nullptr;
	CurrentPlayingNode = nullptr;
	PlayingBranchName = {};
}

void UDialogueManagerBase::PlayDialogueNode(TObjectPtr<UDialogueNode> Node)
{
	CurrentPlayingNode = Node;
	Node->OnPlayed(ComponentPlayingDialogue);
	OnPlayedDialogueNode.Broadcast(Node);
}

bool UDialogueManagerBase::IsPlayingDialogueNode() const
{
	return IsValid(CurrentPlayingNode);
}
