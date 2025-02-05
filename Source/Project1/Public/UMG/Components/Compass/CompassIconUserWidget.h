// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG/Project1UserWidgetBase.h"
#include "CompassIconUserWidget.generated.h"

class UImage;
class UCompassBarUserWidget;

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
	TObjectPtr<UCompassBarUserWidget> OwningCompassBar{ nullptr };
	FDelegateHandle OwningCompassBarBackgroundScrollUAxisValueChangedDelegateHandle{};

public:
	UFUNCTION(BlueprintImplementableEvent)
	UImage* GetImage();

	UFUNCTION(BlueprintCallable, Category = "CompassIconUserWidget")
	void SetIconTexture(UTexture2D* Texture);

	UFUNCTION(BlueprintCallable, Category = "CompassIconUserWidget")
	void SetIconTint(const FSlateColor& Tint);

	UFUNCTION(BlueprintCallable, Category = "CompassIconUserWidget")
	void SetWorldLocation(const FVector& WorldLocation);

	void SetOwningCompassBar(TObjectPtr<UCompassBarUserWidget> CompassBar);
	void UpdateIconScrollUAxisValue();

private:
	void NativeOnInitialized() override;
};
