#pragma once

#include "CoreMinimal.h"
#include "PickupSaveData.generated.h"

USTRUCT(BlueprintType)
struct FPickupSaveData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	bool bPickedUp{ false };
};