// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"
#include "DialogueManagerBase.generated.h"

class UDialogueScreen;
class UDialogueNode;
class AProject1HUDBase;

/**
 *
 */
UCLASS(Blueprintable, BlueprintType)
class PROJECT1_API UDialogueManagerBase : public UObject
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	TSoftClassPtr<UDialogueScreen> DialogueScreenWidgetClass{ nullptr };

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag DialogueScreenWidgetLayerName{};

	TObjectPtr<AProject1HUDBase> Project1HUD{ nullptr };

	UPROPERTY()
	TObjectPtr<UDialogueNode> CurrentPlayingNode{ nullptr };

public:
	void BeginPlay();

	void BeginDialogueBranch(TObjectPtr<UDialogueNode> BranchRootNode);

	const FText* GetCurrentPlayingNodeDialogueLineText() const;

private:
	void PlayDialogueNode(TObjectPtr<UDialogueNode> Node);
};
