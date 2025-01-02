#pragma once

#include "CoreMinimal.h"
#include "UIInputActionKeyMapping.generated.h"

UENUM()
enum class EUIInputAxisSwizzle : uint8
{
	XY UMETA(DisplayName = "XY"),
	YX UMETA(DisplayName = "YX")
};

USTRUCT()
struct FUIInputActionKeyMapping
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FKey Key{};

	UPROPERTY(EditDefaultsOnly)
	float InputValueScale{ 1.0f };

	UPROPERTY(EditDefaultsOnly)
	bool bAcceptRepeatInputs{ false };

	UPROPERTY(EditDefaultsOnly)
	bool bConsumeInput{ true };

	UPROPERTY(EditDefaultsOnly)
	bool bExecuteWhenPaused{ true };

	UPROPERTY(EditDefaultsOnly)
	EUIInputAxisSwizzle InputAxisSwizzle{ EUIInputAxisSwizzle::XY };
};