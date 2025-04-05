// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawns/Characters/Project1CharacterBase.h"
#include "Components/TimelineComponent.h"
#include "PlayerCharacterBase.generated.h"

class UPointLightComponent;
class UCurveFloat;

/**
 * 
 */
UCLASS()
class PROJECT1_API APlayerCharacterBase : public AProject1CharacterBase
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPointLightComponent> GlowPointLight;

	UPROPERTY(EditAnywhere, Category = "PlayerGlowLight")
	TObjectPtr<UCurveFloat> GlowPointLightFadeCurve;

	UPROPERTY(EditAnywhere, Category = "Footsteps")
	TObjectPtr<USoundBase> FootstepSound;
	UPROPERTY(EditAnywhere, Category = "Footsteps")
	TObjectPtr<USoundAttenuation> FootstepSoundAttenuation;

	TObjectPtr<UWorld> World;

	float GlowPointLightIntensity;
	FTimeline GlowPointLightFadeTimeline;
	UPROPERTY()
	TEnumAsByte<ETimelineDirection::Type> GlowPointLightFadeTimelineDirection;

public:
	APlayerCharacterBase(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "PlayerCharacter")
	void SetGlowLightVisibility(const bool NewVisibility);

protected:
	void BeginPlay() override;
	void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void GlowPointLightFadeTimelineProgress(float Value);
	UFUNCTION()
	void GlowPointLightFadeTimelineFinished();
};
