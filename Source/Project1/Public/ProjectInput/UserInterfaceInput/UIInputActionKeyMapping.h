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
	float ValueScale{ 1.0f };

	UPROPERTY(EditDefaultsOnly)
	bool bAcceptRepeatInputs{ false };

	UPROPERTY(EditDefaultsOnly)
	bool bConsumeInput{ true };

	UPROPERTY(EditDefaultsOnly)
	bool bExecuteWhenPaused{ true };
};