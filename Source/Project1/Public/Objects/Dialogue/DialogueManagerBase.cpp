// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueManagerBase.h"
#include "Objects/Dialogue/DialogueNode.h"
#include "UMG/Screens/Game/DialogueScreen.h"
#include "HUDs/Project1HUDBase.h"
#include "Kismet/GameplayStatics.h"

void UDialogueManagerBase::BeginPlay()
{
	Project1HUD = CastChecked<AProject1HUDBase>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
}

void UDialogueManagerBase::BeginDialogueBranch(TObjectPtr<UDialogueNode> BranchRootNode)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::White, FString::Printf(TEXT("Beginning dialogue branch")));

	// Can only play a dialogue branch if one is not already playing
	//if (!Project1HUD->IsPrimaryLayoutWidgetLayerEmpty(DialogueScreenWidgetLayerName))
	//{
	//	return;
	//}

	PlayDialogueNode(BranchRootNode);
	Project1HUD->PushContentToPrimaryLayoutWidgetLayer(DialogueScreenWidgetLayerName, DialogueScreenWidgetClass);
}

const FText* UDialogueManagerBase::GetCurrentPlayingNodeDialogueLineText() const
{
	if (!IsValid(CurrentPlayingNode))
	{
		return nullptr;
	}

	return &(CurrentPlayingNode->GetDialogueLine());
}

void UDialogueManagerBase::PlayDialogueNode(TObjectPtr<UDialogueNode> Node)
{
	CurrentPlayingNode = Node;
}
