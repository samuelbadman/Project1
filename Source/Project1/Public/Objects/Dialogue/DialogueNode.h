// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DialogueNode.generated.h"

class UDialogueComponent;

USTRUCT(BlueprintType)
struct FDialogueOption
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly)
	FText OptionButtonText{};

	// Function must be marked UFUNCTION() or be a blueprint function
	UPROPERTY(EditDefaultsOnly)
	FName CallbackUFunctionName{};
};

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, EditInlineNew, DefaultToInstanced)
class PROJECT1_API UDialogueNode : public UObject
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DialogueNode", meta = (MultiLine = "true", AllowPrivateAccess = "true"))
	FText DialogueLine{};

	UPROPERTY(EditDefaultsOnly)
	FText DialogueOptionModalPromptText{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DialogueNode", meta = (MultiLine = "true", AllowPrivateAccess = "true"))
	TArray<FDialogueOption> DialogueOptions{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DialogueNode", meta = (MultiLine = "true", AllowPrivateAccess = "true"))
	TObjectPtr<UDialogueNode> NextNode{};

public:
	FORCEINLINE const FText& GetDialogueLine() const { return DialogueLine; }
	FORCEINLINE TObjectPtr<UDialogueNode> GetNextDialogueNode() const { return NextNode; }
	FORCEINLINE const FText& GetDialogueOptionModalPromptText() const { return DialogueOptionModalPromptText; }
	FORCEINLINE const TArray<FDialogueOption>& GetDialogueOptions() const { return DialogueOptions; }
	FORCEINLINE bool DefinesDialogueOptions() const { return (DialogueOptions.Num() > 0); }

	UFUNCTION(BlueprintImplementableEvent)
	void OnPlayed(UDialogueComponent* ComponentPlayedDialogue);

	UFUNCTION(BlueprintImplementableEvent)
	void Tick(float DeltaSeconds, UDialogueComponent* ComponentPlayedDialogue);

	UFUNCTION(BlueprintImplementableEvent)
	void OnFinished(UDialogueComponent* ComponentPlayedDialogue);
};
