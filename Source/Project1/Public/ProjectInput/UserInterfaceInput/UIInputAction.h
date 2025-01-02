// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UIInputAction.generated.h"

UENUM()
enum class EUIInputValueType : uint8
{
	Float1D UMETA(DisplayName = "Float"),
	FVector2D UMETA(DisplayName = "FVector2D")
};

/**
 * 
 */
UCLASS(meta = (DisplayName = "UI Input Action"))
class UUIInputAction : public UDataAsset
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly, meta = (DisplayName = "UI Input Value Type"))
	EUIInputValueType UIInputValueType{ EUIInputValueType::Float1D };

public:
	FORCEINLINE EUIInputValueType GetInputValueType() const { return UIInputValueType; }
};
