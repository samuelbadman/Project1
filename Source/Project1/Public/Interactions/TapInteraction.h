// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactions/InteractionBase.h"
#include "TapInteraction.generated.h"

/**
 * 
 */
UCLASS()
class UTapInteraction : public UInteractionBase
{
	GENERATED_BODY()
	
private:
	float BaseIncrementAmount{ 0.0f };
	float DecayRate{ 0.0f };
	TObjectPtr<UCurveFloat> IncrementAmountCurveModifier{ nullptr };

public:
	virtual EInteractionType GetType() const override { return EInteractionType::Tap; }

private:
	virtual void Initialize(const FInteractionDescription& Desc) override;
	virtual void OnInteractInputPressed() override;
	virtual void Tick(float DeltaTime) override;

	float CalculateDecayAmount(float DeltaTime) const;
};
