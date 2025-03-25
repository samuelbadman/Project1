// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterBase.h"
#include "Components/PointLightComponent.h"
#include "FunctionLibraries/Project1CharacterLibrary.h"

APlayerCharacterBase::APlayerCharacterBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	FootstepSound(nullptr),
	FootstepSoundAttenuation(nullptr),
	World(nullptr)
{
	// Set actor tick
	PrimaryActorTick.bCanEverTick = true;
	// Create glow point light component. Disable by default
	GlowPointLight = CreateDefaultSubobject<UPointLightComponent>(FName(TEXT("GlowPointLightComponent")));
	GlowPointLight->SetupAttachment(RootComponent);
	GlowPointLight->SetCastShadows(false);
	GlowPointLightIntensity = 15000000.0f;
	GlowPointLight->SetIntensity(GlowPointLightIntensity);
	GlowPointLight->SetVisibility(false);
	// Player is only affected by lights in lighting channel 1
	GetMesh()->LightingChannels.bChannel0 = 0;
	GetMesh()->LightingChannels.bChannel1 = 1;
	// Initialize glow point light fade timeline
	GlowPointLightFadeCurve = nullptr;
	GlowPointLightFadeTimeline = {};
}

void APlayerCharacterBase::SetGlowLightVisibility(const bool NewVisibility)
{
	if (NewVisibility)
	{
		// Turning on glow point light, bring light intensity up gradually over time
		GlowPointLight->SetVisibility(true);
		GlowPointLightFadeTimeline.Play();
	}
	else
	{
		// Turning off glow point light, bring light intensity down gradually over time
		GlowPointLightFadeTimeline.Reverse();
	}
}

void APlayerCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	// Get world
	World = GetWorld();

	// Setup glow point light fade timeline
	FOnTimelineFloat GlowPointLightFadeTimelineInterpFunc{};
	GlowPointLightFadeTimelineInterpFunc.BindUFunction(this, FName(TEXT("GlowPointLightFadeTimelineProgress")));
	GlowPointLightFadeTimeline.AddInterpFloat(GlowPointLightFadeCurve, GlowPointLightFadeTimelineInterpFunc);

	FOnTimelineEvent GlowPointLightFadeTimelineFinishedFunc{};
	GlowPointLightFadeTimelineFinishedFunc.BindUFunction(this, FName(TEXT("GlowPointLightFadeTimelineFinished")));
	GlowPointLightFadeTimeline.SetTimelineFinishedFunc(GlowPointLightFadeTimelineFinishedFunc);

	GlowPointLightFadeTimeline.SetPropertySetObject(this);
	GlowPointLightFadeTimeline.SetDirectionPropertyName(FName(TEXT("GlowPointLightFadeTimelineDirection")));
}

void APlayerCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Tick glow point light fade timeline
	GlowPointLightFadeTimeline.TickTimeline(DeltaTime);
}

void APlayerCharacterBase::OnFootstepNotify(const FName& FootBoneName)
{
	Super::OnFootstepNotify(FootBoneName);

	UProject1CharacterLibrary::PlayFootstepFX(World, GetMesh(), FootBoneName, FootstepSound, FootstepSoundAttenuation);
}

void APlayerCharacterBase::GlowPointLightFadeTimelineProgress(float Value)
{
	GlowPointLight->SetIntensity(GlowPointLightIntensity * Value);
}

void APlayerCharacterBase::GlowPointLightFadeTimelineFinished()
{
	if (GlowPointLightFadeTimelineDirection == ETimelineDirection::Backward)
	{
		GlowPointLight->SetVisibility(false);
	}
}
