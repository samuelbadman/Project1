// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameModes/GameGameMode.h"
#include "Objects/Dialogue/DialogueManagerBase.h"

UDialogueComponent::UDialogueComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UDialogueComponent::PlayBranch(const FGameplayTag& Branch)
{
	DialogueManager->BeginDialogueBranch(Branch, this);
}

void UDialogueComponent::NotifyDialogueBranchCompleted(const FGameplayTag& CompletedBranch)
{
	OnDialogueBranchComplete.Broadcast(CompletedBranch);
}

void UDialogueComponent::BeginPlay()
{
	Super::BeginPlay();
	DialogueManager = CastChecked<AGameGameMode>(UGameplayStatics::GetGameMode(this))->GetDialogueManager();
}
