// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG/Project1UserWidgetBase.h"
#include "CompassIconUserWidget.generated.h"

class UImage;

/**
 * 
 */
UCLASS()
class PROJECT1_API UCompassIconUserWidget : public UProject1UserWidgetBase
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly)
	FName ScrollUAxisMaterialParameterName;

	UPROPERTY(EditDefaultsOnly)
	FName IconTextureParameterName;

	TObjectPtr<UMaterialInstanceDynamic> ImageDynamicMaterialInstance{ nullptr };
	FVector TargetWorldLocation{ FVector::ZeroVector };

public:
	UFUNCTION(BlueprintImplementableEvent)
	UImage* GetImage();

	void SetIconTexture(TObjectPtr<UTexture2D> Texture);
	void SetIconTint(const FSlateColor& Tint);
	void SetWorldLocation(const FVector& WorldLocation);
	void UpdateIconScrollUAxisValue(float CurrentCompassBarBackgroundScrollUValue);

private:
	void NativeOnInitialized();
};
