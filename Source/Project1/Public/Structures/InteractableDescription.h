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

	// The amount of time the interact input must be held for to complete the interaction. Only used when InteractionType is set to hold
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InteractableDescription")
	float HoldInteractionDurationSeconds{ 0.1f };

	// The amount of completion percent that is added to the interaction each time the interact input is pressed during a tap interaction. Completion percent is in the
	// range 0 - 1. Only used when InteractionType is set to tap
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InteractableDescription")
	float TapInteractionPercentCompleteIncrementAmount{ 0.2f };

	// Curve float asset used to modify the TapInteractionPercentCompleteIncrementAmount based on the completion percentage of the interaction. The curve should be in the time range
	// 0 - 1 and sampled values are multiplied with TapInteractionPercentCompleteIncrementAmount. Time values outside the 0 - 1 range are not sampled. For example, the curve would 
	// usually contain a point starting at 0, 1 and an ending point at 1, X. X is the final value multiplied with TapInteractionPercentCompleteIncrementAmount as the interaction
	// completion percent increases. Points in between these two describe how the multiplier gets to the final value X. Only used when interaction type is set to tap
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InteractableDescription")
	TObjectPtr<UCurveFloat> TapInteractionIncrementAmountCurveModifier{ nullptr };

	// The rate that the completion percent of a tap interaction reduces at over time. Only used when InteractionType is set to tap
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InteractableDescription")
	float TapInteractionDecayRate{ 0.0f };
};