#pragma once

#include "CoreMinimal.h"
#include "InteractableDescription.generated.h"

UENUM()
enum class EInteractableInteractionType : uint8
{
	Press,
	Hold,
	Mash
};

USTRUCT(BlueprintType)
struct FInteractableDescription
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText InteractActionText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EInteractableInteractionType InteractionType{ EInteractableInteractionType::Press };

	// Only used when interaction type is set to hold
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HoldInteraction")
	float HoldInteractDuration{ 2.5f };

	FInteractableDescription();
};
