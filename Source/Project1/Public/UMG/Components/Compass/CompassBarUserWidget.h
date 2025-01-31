// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG/Project1UserWidgetBase.h"
#include "CompassBarUserWidget.generated.h"

class UImage;
class AGamePlayerCameraManager;

/**
 * 
 */
UCLASS()
class PROJECT1_API UCompassBarUserWidget : public UProject1UserWidgetBase
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly)
	FName ScrollUAxisMaterialParameterName;

	TObjectPtr<AGamePlayerCameraManager> PlayerCameraManager{ nullptr };
	TObjectPtr<UMaterialInstanceDynamic> BackgroundBarDynamicMaterialInstance{ nullptr };
	FDelegateHandle PlayerCameraUpdatedDelegateHandle{};

public:
	UFUNCTION(BlueprintImplementableEvent)
	UImage* GetBackgroundImage();

private:
	void NativeOnInitialized() override;
	void NativeDestruct() override;

	void OnPlayerCameraUpdated(float CurrentPitch, float CurrentYaw);
};
