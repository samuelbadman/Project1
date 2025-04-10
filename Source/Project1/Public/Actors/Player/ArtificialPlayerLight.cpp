// Fill out your copyright notice in the Description page of Project Settings.


#include "ArtificialPlayerLight.h"
#include "Components/PointLightComponent.h"

AArtificialPlayerLight::AArtificialPlayerLight()
	:
	PointLightFadeCurve(nullptr),
	PointLightComponentIntensity(15000000.0f),
	PointLightFadeTimeline({}),
	PointLightFadeTimelineDirection(ETimelineDirection::Forward)
{
	PrimaryActorTick.bCanEverTick = true;

	// Create point light component. Set not visible by default
	PointLightComponent = CreateDefaultSubobject<UPointLightComponent>(FName(TEXT("PointLightComponent")));
	RootComponent = PointLightComponent;
	PointLightComponent->SetCastShadows(false);
	PointLightComponent->SetIntensity(PointLightComponentIntensity);
	PointLightComponent->SetVisibility(false);
	PointLightComponent->SetLightingChannels(true, false, false);
}

void AArtificialPlayerLight::SetLightVisibility(bool NewVisibility)
{
	if (NewVisibility)
	{
		// Turning on point light, bring light intensity up gradually over time
		PointLightComponent->SetVisibility(true);
		PointLightFadeTimeline.Play();
	}
	else
	{
		// Turning off point light, bring light intensity down gradually over time
		PointLightFadeTimeline.Reverse();
	}
}

void AArtificialPlayerLight::BeginPlay()
{
	Super::BeginPlay();

	// Setup point light fade timeline
	FOnTimelineFloat PointLightFadeTimelineInterpFunc{};
	PointLightFadeTimelineInterpFunc.BindUFunction(this, FName(TEXT("PointLightFadeTimelineProgress")));
	PointLightFadeTimeline.AddInterpFloat(PointLightFadeCurve, PointLightFadeTimelineInterpFunc);

	FOnTimelineEvent PointLightFadeTimelineFinishedFunc{};
	PointLightFadeTimelineFinishedFunc.BindUFunction(this, FName(TEXT("PointLightFadeTimelineFinished")));
	PointLightFadeTimeline.SetTimelineFinishedFunc(PointLightFadeTimelineFinishedFunc);

	PointLightFadeTimeline.SetPropertySetObject(this);
	PointLightFadeTimeline.SetDirectionPropertyName(FName(TEXT("PointLightFadeTimelineDirection")));
}

void AArtificialPlayerLight::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// Tick point light fade timeline
	PointLightFadeTimeline.TickTimeline(DeltaSeconds);
}

void AArtificialPlayerLight::PointLightFadeTimelineProgress(float Value)
{
	PointLightComponent->SetIntensity(PointLightComponentIntensity * Value);
}

void AArtificialPlayerLight::PointLightFadeTimelineFinished()
{
	if (PointLightFadeTimelineDirection == ETimelineDirection::Backward)
	{
		PointLightComponent->SetVisibility(false);
	}
}
