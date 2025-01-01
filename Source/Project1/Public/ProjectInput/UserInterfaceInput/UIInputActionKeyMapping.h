#pragma once

#include "CoreMinimal.h"
#include "UIInputActionKeyMapping.generated.h"

USTRUCT()
struct FUIInputActionKeyMapping
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FKey Key{};

	UPROPERTY(EditDefaultsOnly)
	bool bAcceptRepeatInputs{ false };

	UPROPERTY(EditDefaultsOnly)
	float ValueScale{ 1.0f };
};