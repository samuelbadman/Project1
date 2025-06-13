#pragma once

class UCurveFloat;

struct FInteractionDescription
{
	float HoldDurationSeconds{ 0.1f };
	float TapIncrementAmount{ 0.2f };
	TObjectPtr<UCurveFloat> TapIncrementAmountCurveModifier{ nullptr };
	float TapDecayRate{ 0.0f };
};