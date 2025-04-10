// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Project1ActorBase.h"
#include "Components/TimelineComponent.h"
#include "ArtificialPlayerLight.generated.h"

class UPointLightComponent;
class UCurveFloat;

/**
 * 
 */
UCLASS()
class AArtificialPlayerLight : public AProject1ActorBase
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UPointLightComponent> PointLightComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UCurveFloat> PointLightFadeCurve;

	// TODO: On point light component intensity property changed, update this variable to the same value
	float PointLightComponentIntensity;
	FTimeline PointLightFadeTimeline;

	UPROPERTY()
	TEnumAsByte<ETimelineDirection::Type> PointLightFadeTimelineDirection;

public:
	AArtificialPlayerLight();

	void SetLightVisibility(bool NewVisibility);

protected:
	void BeginPlay() override;
	void Tick(float DeltaSeconds) override;

private:
	UFUNCTION()
	void PointLightFadeTimelineProgress(float Value);

	UFUNCTION()
	void PointLightFadeTimelineFinished();
};
