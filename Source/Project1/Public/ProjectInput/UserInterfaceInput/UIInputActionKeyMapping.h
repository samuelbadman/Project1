#pragma once

#include "CoreMinimal.h"
#include "UIInputAxisSwizzle.h"
#include "UIInputActionKeyMapping.generated.h"

USTRUCT()
struct FUIInputActionKeyMapping
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FKey Key{};

	UPROPERTY(EditDefaultsOnly)
	float InputValueScale{ 1.0f };

	UPROPERTY(EditDefaultsOnly)
	bool bAcceptRepeatInputs{ false };

	UPROPERTY(EditDefaultsOnly)
	EUIInputAxisSwizzle InputAxisSwizzle{ EUIInputAxisSwizzle::XY };

	UPROPERTY(EditDefaultsOnly)
	bool bExcludeInputKeys{ false };

	UPROPERTY(EditDefaultsOnly, meta = (EditCondition = "bExcludeInputKeys"))
	TArray<FKey> ExcludedKeys{};
};