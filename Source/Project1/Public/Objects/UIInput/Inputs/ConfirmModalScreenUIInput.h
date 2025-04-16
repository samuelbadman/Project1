#pragma once

#include "CoreMinimal.h"
#include "UIInputBase.h"
#include "ConfirmModalScreenUIInput.generated.h"

class UEnhancedInputLocalPlayerSubsystem;
class UEnhancedInputComponent;
class UInputMappingContext;
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
	TObjectPtr<UInputMappingContext> InputMappingContext{ nullptr };

	UPROPERTY(EditDefaultsOnly)
	int32 InputPriority{ 15 };

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> ConfirmInputAction{ nullptr };

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> NavigateInputAction{ nullptr };

public:
	void SetupInput(TObjectPtr<UEnhancedInputComponent> InputComponent) override;

private:
	TObjectPtr<UInputMappingContext> GetInputMappingContext() const override;
	int32 GetInputPriority() const override;

	void OnConfirmTriggered(const FInputActionValue& Value);
	void OnNavigateTriggered(const FInputActionValue& Value);
};