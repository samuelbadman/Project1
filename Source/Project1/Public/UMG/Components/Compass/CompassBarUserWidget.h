// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG/Project1UserWidgetBase.h"
#include "CompassBarUserWidget.generated.h"

class UImage;
class UOverlay;
class AGamePlayerCameraManager;
class UCompassIconUserWidget;

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

	UPROPERTY(EditDefaultsOnly)
	TSoftClassPtr<UCompassIconUserWidget> CompassIconWidgetClass{ nullptr };

	TObjectPtr<AGamePlayerCameraManager> PlayerCameraManager{ nullptr };
	TObjectPtr<UMaterialInstanceDynamic> BackgroundBarDynamicMaterialInstance{ nullptr };
	FDelegateHandle PlayerCameraUpdatedDelegateHandle{};
	TSubclassOf<UCompassIconUserWidget> LoadedCompassIconWidgetClass{ nullptr };
	TArray<TObjectPtr<UCompassIconUserWidget>> IconWidgets{};

public:
	UFUNCTION(BlueprintImplementableEvent)
	UImage* GetBackgroundImage() const;

	UFUNCTION(BlueprintImplementableEvent)
	UOverlay* GetBarOverlay() const;

	UFUNCTION(BlueprintCallable, Category = "CompassBarUserWidget")
	UCompassIconUserWidget* AddCompassIcon(UTexture2D* IconTexture, const FSlateColor& IconTint, const FVector& WorldLocation);

	UFUNCTION(BlueprintCallable, Category = "CompassBarUserWidget")
	void RemoveCompassIcon(UPARAM(ref) UCompassIconUserWidget*& IconWidget);

	float GetCurrentBackgroundBarScrollUOffset() const;

private:
	void NativeOnInitialized() override;
	void NativeDestruct() override;

	void OnPlayerCameraUpdated(float CurrentPitch, float CurrentYaw);
};
