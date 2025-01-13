// Fill out your copyright notice in the Description page of Project Settings.


#include "Project1BlueprintFunctionLibrary.h"
#include "Kismet/KismetMathLibrary.h"

double UProject1BlueprintFunctionLibrary::ConvertEulerAngleTo360Degrees(const double Euler)
{
	return ((Euler < 0.0) ? Euler + 360.0 : Euler);
}

double UProject1BlueprintFunctionLibrary::Normalize360DegreesAngle(const double Angle)
{
	return UKismetMathLibrary::MapRangeClamped(Angle, 0.0, 360.0, 0.0, 1.0);
}

int32 UProject1BlueprintFunctionLibrary::WrapIncrementArrayIndex(const int32 Index, const int32 ArrayElementCount, const int32 IncrementAmount)
{
	return (Index + ArrayElementCount + IncrementAmount) % ArrayElementCount;
}
