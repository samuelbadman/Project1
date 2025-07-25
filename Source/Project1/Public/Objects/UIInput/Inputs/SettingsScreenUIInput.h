#pragma once

#include "CoreMinimal.h"
#include "UIInputBase.h"
#include "SettingsScreenUIInput.generated.h"

class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnTabTriggeredDelegate, const FInputActionValue& /* Value */);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnCancelTriggeredDelegate, const FInputActionValue& /* Value */);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnNavigateTriggeredDelegate, const FInputActionValue& /* Value */);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnNavigateContinuousTriggeredDelegate, const FInputActionValue& /* Value */);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnConfirmTriggeredDelegate, const FInputActionValue& /* Value */);

UCLASS()
class PROJECT1_API USettingsScreenUIInput : public UUIInputBase
{
	GENERATED_BODY()

public:
	FOnCancelTriggeredDelegate TabTriggeredDelegate{};
	FOnCancelTriggeredDelegate CancelTriggeredDelegate{};
	FOnNavigateTriggeredDelegate NavigateTriggeredDelegate{};
	FOnNavigateContinuousTriggeredDelegate NavigateContinuousTriggeredDelegate{};
	FOnConfirmTriggeredDelegate ConfirmTriggeredDelegate{};

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> TabInputAction{ nullptr };

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> CancelInputAction{ nullptr };

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> NavigateInputAction{ nullptr };

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> NavigateContinuousInputAction{ nullptr };

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> ConfirmInputAction{ nullptr };

private:
	void SetupInput(TObjectPtr<UEnhancedInputComponent> InputComponent) override;

	void OnTabTriggered(const FInputActionValue& Value);
	void OnCancelTriggered(const FInputActionValue& Value);
	void OnNavigateTriggered(const FInputActionValue& Value);
	void OnNavigateContinuousTriggered(const FInputActionValue& Value);
	void OnConfirmTriggered(const FInputActionValue& Value);
};