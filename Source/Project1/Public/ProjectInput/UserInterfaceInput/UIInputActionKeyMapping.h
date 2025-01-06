#pragma once

#include "CoreMinimal.h"
#include "UIInputAxisSwizzle.h"
#include "UIInputActionKeyMapping.generated.h"

USTRUCT()
struct FKeyProperties
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	float InputValueScale{ 1.0f };

	UPROPERTY(EditDefaultsOnly)
	EUIInputAxisSwizzle InputAxisSwizzle{ EUIInputAxisSwizzle::XY };

	UPROPERTY(EditDefaultsOnly)
	bool bExcludeInputKeys{ false };

	UPROPERTY(EditDefaultsOnly, meta = (EditCondition = "bExcludeInputKeys"))
	TArray<FKey> ExcludedKeys{};
};

USTRUCT()
struct FUIInputActionKeyMapping
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TMap<FKey, FKeyProperties> Keys{};
};