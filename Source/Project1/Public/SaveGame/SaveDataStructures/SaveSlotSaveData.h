#pragma once

#include "CoreMinimal.h"
#include "SaveGame/SaveManager.h"
#include "SaveSlotSaveData.generated.h"

USTRUCT(BlueprintType)
struct FSaveSlotSaveData
{
	GENERATED_BODY()

	// Unique id
	UPROPERTY(BlueprintReadOnly)
	int32 Id{ 0 };

	// Unique name
	UPROPERTY(BlueprintReadOnly)
	FName UniqueSlotName{ NAME_None };

	// TODO: Other info that gets displayed on the slot such as time saved, in-game location/level name, screenshot thumbnail, etc...
};