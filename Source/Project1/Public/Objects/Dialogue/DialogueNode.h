// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DialogueNode.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, EditInlineNew, DefaultToInstanced)
class PROJECT1_API UDialogueNode : public UObject
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DialogueNode", meta = (MultiLine = "true", AllowPrivateAccess = "true"))
	FText DialogueLine{};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DialogueNode", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UDialogueNode> NextNode{};

public:
	FORCEINLINE const FText& GetDialogueLine() const { return DialogueLine; }
	FORCEINLINE TObjectPtr<UDialogueNode> GetNextDialogueNode() const { return NextNode; }
};
