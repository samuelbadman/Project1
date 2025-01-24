// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerControllers/Project1PlayerControllerBase.h"
#include "TitleScreenPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UProject1GameViewportClientBase;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPressAnyInputTriggeredDelegate, const FInputActionValue& /* Value */);

/**
 * 
 */
UCLASS()
class PROJECT1_API ATitleScreenPlayerController : public AProject1PlayerControllerBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	bool bLockMouseToViewportWhenShown{ false };

	UPROPERTY(EditAnywhere)
	bool bCenterMouseInViewportWhenShown{ false };

	FOnPressAnyInputTriggeredDelegate PressAnyInputTriggered{};

private:
	UPROPERTY(EditDefaultsOnly, Category = "Input|PressAnyInput")
	TObjectPtr<UInputMappingContext> PressAnyInputInputMappingContext{ nullptr };

	UPROPERTY(EditDefaultsOnly, Category = "Input|PressAnyInput")
	int32 PressAnyInputMappingContextPriority{ 10 };

	UPROPERTY(EditDefaultsOnly, Category = "Input|PressAnyInput")
	TObjectPtr<UInputAction> PressAnyInputInputAction{ nullptr };

	TObjectPtr<UProject1GameViewportClientBase> Project1GameViewportClient{ nullptr };
	FDelegateHandle OnMouseMovedDelegateHandle{};
	FDelegateHandle OnInputKeyDelegateHandle{};

public:
	void AddPressAnyInputInputMappingContext();
	void RemovePressAnyInputInputMappingContext();

private:
	void SetupInputComponent() override;
	void BeginPlay() override;
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void OnPressAnyInputTriggered(const FInputActionValue& Value);
};
