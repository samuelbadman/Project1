#include "UIInputActionValue.h"

template<>
float FUIInputActionValue::Get<float>() const
{
	return Default1DAxis;
}

template<>
FVector2D FUIInputActionValue::Get<FVector2D>() const
{
	return FVector2D(Default1DAxis, Axis2D);
}

void FUIInputActionValue::Reset()
{
	Default1DAxis = ReleasedValue;
	Axis2D = ReleasedValue;
}
