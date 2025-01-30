// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"
#include "DialogueManagerBase.generated.h"

class UDialogueScreen;
class UDialogueNode;
class AProject1HUDBase;
class UDialogueComponent;
class UDynamicModalScreen;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayedDialogueNodeDelegate, TObjectPtr<UDialogueNode> /* DialogueNode */);

/**
 *
 */
UCLASS(Blueprintable, BlueprintType)
class PROJECT1_API UDialogueManagerBase : public UObject
{
	GENERATED_BODY()

public:
	FOnPlayedDialogueNodeDelegate OnPlayedDialogueNode{};

private:
	UPROPERTY(EditDefaultsOnly, Category = "DialogueScreen")
	TSoftClassPtr<UDialogueScreen> DialogueScreenWidgetClass{ nullptr };

	UPROPERTY(EditDefaultsOnly, Category = "DialogueScreen")
	FGameplayTag DialogueScreenWidgetLayerName{};

	UPROPERTY(EditDefaultsOnly, Category = "DynamicModal")
	TSoftClassPtr<UDynamicModalScreen> DynamicModalWidgetClass{ nullptr };

	UPROPERTY(EditDefaultsOnly, Category = "DynamicModal")
	FGameplayTag ModalWidgetLayerName{};

	TObjectPtr<AProject1HUDBase> Project1HUD{ nullptr };

	TObjectPtr<UDialogueComponent> ComponentPlayingDialogue{ nullptr };
	UPROPERTY()
	TObjectPtr<UDialogueNode> CurrentPlayingNode{ nullptr };
	FGameplayTag PlayingBranchName{};

public:
	void BeginPlay();

	void BeginDialogueBranch(const FGameplayTag& BranchName, TObjectPtr<UDialogueComponent> Component);
	void ProgressDialogue();

private:
	void PlayDialogueNode(TObjectPtr<UDialogueNode> Node);
};
