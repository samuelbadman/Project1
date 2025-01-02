#pragma once

#include "CoreMinimal.h"
#include "UIInputActionValue.generated.h"

USTRUCT()
struct FUIInputActionValue
{
	GENERATED_BODY()

	friend class UScreenUserWidgetBase;

private:
	static constexpr float InvalidValue{ -1.0f };
	static constexpr float PressedValue{ 1.0f };
	static constexpr float ReleasedValue{ 0.0f };

private:
	float Default1DAxis{ InvalidValue };
	float Axis2D{ InvalidValue };

public:
	template <typename T>
	T Get() const;
};