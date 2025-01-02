#pragma once

#include "CoreMinimal.h"
#include "UIInputActionValue.h"
#include "UIInputBinding.generated.h"

class UUIInputAction;
class UInputKeyStateController;
struct FUIInputActionKeyMapping;

USTRUCT()
struct FUIInputBinding
{
	GENERATED_BODY()

public:
	TObjectPtr<UUIInputAction> InputAction{ nullptr };
	TDelegate<void(const FUIInputActionValue&)> Event{ nullptr };

private:
	FUIInputActionValue InputValue{};

public:
	void OnBoundUIInputActionInput(UInputKeyStateController& InputKeyStateController, EInputEvent InputEvent, const FUIInputActionKeyMapping& KeyMapping);
};
