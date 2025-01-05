#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UIInputActionValue.h"
#include "UIInputActionKeyMapping.h"
#include "UIInputBinding.generated.h"

class UUIInputAction;
class UInputKeyStateController;

USTRUCT()
struct FUIInputBinding
{
	GENERATED_BODY()

public:
	TObjectPtr<UUIInputAction> InputAction{ nullptr };
	TDelegate<void(const FUIInputActionValue&)> Event{ nullptr };
	TArray<FUIInputActionKeyMapping> KeyMappings{};

private:
	FUIInputActionValue InputValue{};

public:
	void OnBoundUIInputActionInput(const FKey& InputKey, EInputEvent InputEvent, const FUIInputActionKeyMapping& KeyMapping);
};
