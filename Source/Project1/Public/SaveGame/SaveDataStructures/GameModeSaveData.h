#pragma once

#include "CoreMinimal.h"
#include "Structures/PlayTime.h"
#include "GameModeSaveData.generated.h"

USTRUCT(BlueprintType)
struct FGameModeSaveData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FPlayTime TotalPlayTime{};
};