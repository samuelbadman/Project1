// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UIInputActionKeyMapping.h"
#include "UIInputActionMapping.generated.h"

class UUIInputAction;

/**
 * 
 */
UCLASS(meta = (DisplayName = "UI Input Action Mapping"))
class UUIInputActionMapping : public UDataAsset
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly, meta = (DisplayThumbnail = "false"))
	TMap<TObjectPtr<UUIInputAction>, FUIInputActionKeyMapping> ActionMapping{};

public:
	FORCEINLINE const TMap<TObjectPtr<UUIInputAction>, FUIInputActionKeyMapping>& GetActionMapping() const { return ActionMapping; }
};
