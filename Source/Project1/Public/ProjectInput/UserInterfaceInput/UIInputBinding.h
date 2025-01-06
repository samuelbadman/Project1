#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UIInputActionValue.h"
#include "UIInputActionKeyMapping.h"
#include "UIInputBinding.generated.h"

class UUIInputAction;

USTRUCT()
struct FUIInputBinding
{
	GENERATED_BODY()

public:
	TObjectPtr<UUIInputAction> InputAction{ nullptr };
	TDelegate<void(const FUIInputActionValue&)> Event{ nullptr };
	FUIInputActionKeyMapping KeyMapping{};

private:
	FUIInputActionValue InputValue{};

public:
	void OnBoundUIInputActionInput(const FKey& InputKey, EInputEvent InputEvent);
};
