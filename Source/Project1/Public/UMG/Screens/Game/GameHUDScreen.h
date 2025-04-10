// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG/Screens/ScreenUserWidgetBase.h"
#include "GameHUDScreen.generated.h"

class UCompassBarUserWidget;

UENUM()
enum class EGameHUDScreenFadeDirection : uint8
{
	In,
	Out
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnScreenFadeOutCompleteSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnScreenFadeInCompleteSignature);

/**
 *
 */
UCLASS()
class UGameHUDScreen : public UScreenUserWidgetBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnScreenFadeOutCompleteSignature ScreenFadeOutComplete;

	UPROPERTY(BlueprintAssignable)
	FOnScreenFadeInCompleteSignature ScreenFadeInComplete;

private:
	static constexpr float ScreenFadeOutTargetRenderOpacity{ 0.0f };
	static constexpr float ScreenFadeInTargetRenderOpacity{ 1.0f };

	float TargetScreenRenderOpacity;
	float CurrentScreenFadeInterpRate;
	bool bShouldUpdateRenderOpacity;
	FTimerHandle ScreenFadeDelayTimerHandle;

public:
	UGameHUDScreen();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	UCompassBarUserWidget* GetCompassBarWidget() const;

	UFUNCTION(BlueprintCallable, Category = "GameHUDScreen")
	void FadeScreen(EGameHUDScreenFadeDirection Direction, float Rate = 1.0f);

	UFUNCTION(BlueprintCallable, Category = "GameHUDScreen")
	void FadeScreenAfterDelay(EGameHUDScreenFadeDirection Direction, float Rate = 1.0f, float DelayDuration = 0.2f);

protected:
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	void BeginScreenFade(float TargetRenderOpacity, float FadeRate);

	void OnScreenFadeOutComplete();
	void OnScreenFadeInComplete();
};
