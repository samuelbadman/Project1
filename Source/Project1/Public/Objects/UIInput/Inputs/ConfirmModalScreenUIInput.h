#pragma once

#include "CoreMinimal.h"
#include "UIInputBase.h"
#include "ConfirmModalScreenUIInput.generated.h"

class UEnhancedInputLocalPlayerSubsystem;
class UEnhancedInputComponent;
class UInputAction;
struct FInputActionValue;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnConfirmTriggeredDelegate, const FInputActionValue& /* Value */);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnNavigateTriggeredDelegate, const FInputActionValue& /* Value */);

UCLASS()
class PROJECT1_API UConfirmModalScreenUIInput : public UUIInputBase
{
	GENERATED_BODY()

public:
	FOnConfirmTriggeredDelegate ConfirmTriggeredDelegate{};
	FOnNavigateTriggeredDelegate NavigateTriggeredDelegate{};

private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> ConfirmInputAction{ nullptr };

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> NavigateInputAction{ nullptr };

public:
	void SetupInput(TObjectPtr<UEnhancedInputComponent> InputComponent) override;

private:
	void OnConfirmTriggered(const FInputActionValue& Value);
	void OnNavigateTriggered(const FInputActionValue& Value);
};