#pragma once

#include "CoreMinimal.h"
#include "SaveGame/SaveManager.h"
#include "SaveSlotSaveData.generated.h"

// Stores save information about a save slot. Used to reconstruct save slots when the game is started
USTRUCT(BlueprintType)
struct FSaveSlotSaveData
{
	GENERATED_BODY()

	// Slot unique id
	UPROPERTY(BlueprintReadOnly)
	int32 Id{ 0 };

	// Slot unique name
	UPROPERTY(BlueprintReadOnly)
	FName UniqueSlotName{ NAME_None };

	// The date and time the slot was last saved into as a string representation
	UPROPERTY(BlueprintReadOnly)
	FName TimeDateSaved{ NAME_None };

	// TODO: Other info that gets displayed on the slot such as time saved, in-game location/level name, screenshot thumbnail, etc...
};