#pragma once

#include "CoreMinimal.h"
#include "Enumerations/InteractionType.h"
#include "InteractableDescription.generated.h"

USTRUCT(BlueprintType)
struct FInteractableDescription
{
	GENERATED_BODY()

	// The interact action text displayed in the interact prompt screen for the interactable
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InteractableDescription")
	FName InteractActionText{ NAME_None };

	// The type of interaction this interactable will be interacted with through
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InteractableDescription")
	EInteractionType InteractionType{ EInteractionType::SinglePress };
};