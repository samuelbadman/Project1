// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterBase.h"
#include "Components/PointLightComponent.h"

APlayerCharacterBase::APlayerCharacterBase()
{
	// Create glow point light component. Disable by default
	GlowPointLight = CreateDefaultSubobject<UPointLightComponent>(FName(TEXT("GlowPointLightComponent")));
	GlowPointLight->SetupAttachment(RootComponent);
	GlowPointLight->SetCastShadows(false);
	SetGlowLightVisibility(false);
	// Player is only affected by lights in lighting channel 1
	GetMesh()->LightingChannels.bChannel0 = 0;
	GetMesh()->LightingChannels.bChannel1 = 1;
}

void APlayerCharacterBase::SetGlowLightVisibility(const bool NewVisibility)
{
	GlowPointLight->SetVisibility(NewVisibility);
}
