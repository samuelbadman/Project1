// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponents/Project1ActorComponentBase.h"
#include "GameplayTagContainer.h"
#include "DialogueComponent.generated.h"

class UDialogueNode;
class UDialogueManagerBase;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJECT1_API UDialogueComponent : public UProject1ActorComponentBase
{
	GENERATED_BODY()
	
private:
	// A branching dialogue is stored inside a tree structure in each dialogue component. A branch is identified by a unique gameplay tag alongside a linked list of dialogue nodes.
	// A dialogue component implements a dialogue for an actor that can be talked to. An actor may have more than 1 dialogue component if necessary. Each dialogue chain down to a
	// leaf of a dialogue branch is stored inside a key:value pair inside the map. Dialogue branches are identified by a human readable key (gameplay tag). Add a new gameplay tag 
	// to add a new branch identifier.
	// DO NOT CHANGE THIS VARIABLE AS IT WILL DELETE ALL DIALOGUES THAT HAVE BEEN SET UP
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DialogueComponent", meta = (AllowPrivateAccess = "true"))
	TMap<FGameplayTag, TObjectPtr<UDialogueNode>> DialogueTree{};

	TObjectPtr<UDialogueManagerBase> DialogueManager{ nullptr };

public:
	UDialogueComponent();

	UFUNCTION(BlueprintCallable)
	void PlayBranch(const FGameplayTag& Branch);

private:
	void BeginPlay() override;
};
