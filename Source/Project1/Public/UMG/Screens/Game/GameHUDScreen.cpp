// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHUDScreen.h"

UGameHUDScreen::UGameHUDScreen()
	:
	TargetScreenRenderOpacity(1.0f),
	CurrentScreenFadeInterpRate(0.0f),
	bShouldUpdateRenderOpacity(false),
	ScreenFadeDelayTimerHandle({})
{
}

void UGameHUDScreen::FadeScreen(EGameHUDScreenFadeDirection Direction, float Rate)
{
	FTimerManager& TimerManager{ GetWorld()->GetTimerManager()};

	if (TimerManager.IsTimerActive(ScreenFadeDelayTimerHandle))
	{
		TimerManager.ClearTimer(ScreenFadeDelayTimerHandle);
	}

	switch (Direction)
	{
	case EGameHUDScreenFadeDirection::Out: BeginScreenFade(ScreenFadeOutTargetRenderOpacity, Rate); break;
	case EGameHUDScreenFadeDirection::In: BeginScreenFade(ScreenFadeInTargetRenderOpacity, Rate); break;
	}
}

void UGameHUDScreen::FadeScreenAfterDelay(EGameHUDScreenFadeDirection Direction, float Rate, float DelayDuration)
{
	FTimerDelegate TimerDel{};
	TimerDel.BindUObject(this, &UGameHUDScreen::FadeScreen, Direction, Rate);
	GetWorld()->GetTimerManager().SetTimer(ScreenFadeDelayTimerHandle, TimerDel, DelayDuration, false);
}

bool UGameHUDScreen::IsScreenFadedOut() const
{
	return (GetRenderOpacity() == ScreenFadeOutTargetRenderOpacity);
}

bool UGameHUDScreen::IsScreenFadeDelayActive() const
{
	return GetWorld()->GetTimerManager().IsTimerActive(ScreenFadeDelayTimerHandle);
}

void UGameHUDScreen::ClearScreenFadeDelayTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(ScreenFadeDelayTimerHandle);
}

void UGameHUDScreen::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (bShouldUpdateRenderOpacity)
	{
		float UpdatedRenderOpacity{ FMath::FInterpConstantTo(GetRenderOpacity(), TargetScreenRenderOpacity, InDeltaTime, CurrentScreenFadeInterpRate) };

		if (FMath::IsNearlyEqual(UpdatedRenderOpacity, TargetScreenRenderOpacity))
		{
			UpdatedRenderOpacity = TargetScreenRenderOpacity;
			bShouldUpdateRenderOpacity = false;

			if (TargetScreenRenderOpacity == ScreenFadeOutTargetRenderOpacity)
			{
				OnScreenFadeOutComplete();
			}
			else if (TargetScreenRenderOpacity == ScreenFadeInTargetRenderOpacity)
			{
				OnScreenFadeInComplete();
			}
		}

		SetRenderOpacity(UpdatedRenderOpacity);
	}
}

void UGameHUDScreen::BeginScreenFade(float TargetRenderOpacity, float FadeRate)
{
	TargetScreenRenderOpacity = TargetRenderOpacity;
	CurrentScreenFadeInterpRate = FadeRate;
	bShouldUpdateRenderOpacity = true;
}

void UGameHUDScreen::OnScreenFadeOutComplete()
{
	ScreenFadeOutComplete.Broadcast();
}

void UGameHUDScreen::OnScreenFadeInComplete()
{
	ScreenFadeInComplete.Broadcast();
}
