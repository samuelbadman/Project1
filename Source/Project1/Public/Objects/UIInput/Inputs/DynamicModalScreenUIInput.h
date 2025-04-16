#pragma once

#include "CoreMinimal.h"
#include "UIInputBase.h"
#include "DynamicModalScreenUIInput.generated.h"

class UEnhancedInputLocalPlayerSubsystem;
class UEnhancedInputComponent;
struct FInputActionValue;
class UInputAction;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnDynamicModalConfirmTriggeredDelegate, const FInputActionValue& /* Value */);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnDynamicModalNavigateTriggeredDelegate, const FInputActionValue& /* Value */);

UCLASS()
class PROJECT1_API UDynamicModalScreenUIInput : public UUIInputBase
{
	GENERATED_BODY()

public:
	FOnDynamicModalConfirmTriggeredDelegate DynamicModalConfirmTriggered{};
	FOnDynamicModalNavigateTriggeredDelegate DynamicModalNavigateTriggered{};

private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> DynamicModalConfirmInputAction{ nullptr };

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> DynamicModalNavigateInputAction{ nullptr };

public:
	void SetupInput(TObjectPtr<UEnhancedInputComponent> InputComponent) override;

private:
	void OnDynamicModalConfirmTriggered(const FInputActionValue& Value);
	void OnDynamicModalNavigateTriggered(const FInputActionValue& Value);
};