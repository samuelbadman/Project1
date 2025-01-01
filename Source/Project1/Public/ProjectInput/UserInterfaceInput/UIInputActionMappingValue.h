#pragma once

#include "CoreMinimal.h"
#include "UIInputActionKeyMapping.h"
#include "UIInputActionMappingValue.generated.h"

USTRUCT()
struct FUIInputActionMappingValue
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TArray<FUIInputActionKeyMapping> Mapping{};
};