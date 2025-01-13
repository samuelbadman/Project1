// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Project1BlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT1_API UProject1BlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	// Returns the in euler angle in the range 0 - 180/-180 degrees to 0 - 360 degrees
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Project1BlueprintFunctionLibrary", meta = (DisplayName = "Convert Euler Angle To 360 Degrees"))
	static double ConvertEulerAngleTo360Degrees(const double Euler);

	// Returns the in angle in the range 0 - 360 degrees normalized to 0 - 1 range
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Project1BlueprintFunctionLibrary", meta = (DisplayName = "Normalize 360 Degrees Angle"))
	static double Normalize360DegreesAngle(const double Angle);

	// Returns Index incremented by IncrementAmount wrapped within the range 0 - ArrayElementCount. Works both ways so, IncrementAmount can be positive or negative
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Project1BlueprintFunctionLibrary", meta = (DisplayName = "Wrap Increment Array Index"))
	static int32 WrapIncrementArrayIndex(const int32 Index, const int32 ArrayElementCount, const int32 IncrementAmount);
};
