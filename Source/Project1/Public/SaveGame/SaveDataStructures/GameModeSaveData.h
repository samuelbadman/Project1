#pragma once

#include "CoreMinimal.h"
#include "Structures/PlayTime.h"
#include "GameModeSaveData.generated.h"

USTRUCT()
struct FGameModeSaveData
{
	GENERATED_BODY()

	UPROPERTY()
	FPlayTime TotalPlayTime{};
};