// Fill out your copyright notice in the Description page of Project Settings.


#include "TapInteraction.h"


void UTapInteraction::Initialize(const FInteractionDescription& Desc)
{
	BaseIncrementAmount = Desc.TapIncrementAmount;
	DecayRate = Desc.TapDecayRate;
	IncrementAmountCurveModifier = Desc.TapIncrementAmountCurveModifier;
}

void UTapInteraction::OnInteractInputPressed()
{
	const float CurrentCompletionPercent{ GetCompletionPercent() };

	// If there is a increment amount curve modifier supplied, sample the curve at completion percent to find out the multiplier value to multiply the base increment amount by
	float IncrementAmount{ BaseIncrementAmount };

	if (IsValid(IncrementAmountCurveModifier))
	{
		IncrementAmount = BaseIncrementAmount * IncrementAmountCurveModifier->GetFloatValue(CurrentCompletionPercent);
	}

	SetCompletionPercent(CurrentCompletionPercent + IncrementAmount);

	if (IsComplete())
	{
		CompleteInteraction();
	}
}

void UTapInteraction::Tick(float DeltaTime)
{
	const float NewCompletionPercent{ GetCompletionPercent() - CalculateDecayAmount(DeltaTime) };

	// Check if the interaction has failed
	if (NewCompletionPercent <= 0.0f)
	{
		// Interaction has failed. Cancel the interaction
		SetCompletionPercent(MinCompletionPercent);
		OnInteractionCanceledDelegate.Broadcast(this);
	}
	else
	{
		// Update completion percent with reduced amount
		SetCompletionPercent(NewCompletionPercent);
	}
}

float UTapInteraction::CalculateDecayAmount(float DeltaTime) const
{
	return DecayRate * DeltaTime;
}
