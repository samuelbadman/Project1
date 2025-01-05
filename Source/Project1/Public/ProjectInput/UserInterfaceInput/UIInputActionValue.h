#pragma once

#include "CoreMinimal.h"
#include "UIInputActionValue.generated.h"

USTRUCT()
struct FUIInputActionValue
{
	GENERATED_BODY()

	friend struct FUIInputBinding;

public:
	static constexpr float PressedValue{ 1.0f };
	static constexpr float ReleasedValue{ 0.0f };

private:
	float Default1DAxis{ ReleasedValue };
	float Axis2D{ ReleasedValue };

public:
	template <typename T>
	T Get() const;

private:
	void Reset();
};