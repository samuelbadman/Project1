// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerControllers/Project1PlayerControllerBase.h"
#include "TitleScreenPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UProject1GameViewportClientBase;
class UPressAnyInputPromptInputMapping;
class UMainMenuScreenInputMapping;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnAnyInputTriggeredDelegate, const FInputActionValue& /* Value */);

DECLARE_MULTICAST_DELEGATE_OneParam(FOnMainMenuScreenConfirmTriggeredDelegate, const FInputActionValue& /* Value */);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnMainMenuScreenNavigateTriggeredDelegate, const FInputActionValue& /* Value */);

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

	FOnAnyInputTriggeredDelegate AnyInputTriggered{};

	FOnMainMenuScreenConfirmTriggeredDelegate MainMenuScreenConfirmTriggered{};
	FOnMainMenuScreenNavigateTriggeredDelegate MainMenuScreenNavigateTriggered{};

private:
	UPROPERTY(EditDefaultsOnly, Category = "Input|PressAnyInputPrompt")
	TObjectPtr<UPressAnyInputPromptInputMapping> PressAnyInputPromptInputMapping{ nullptr };
	UPROPERTY(EditDefaultsOnly, Category = "Input|PressAnyInputPrompt")
	int32 PressAnyInputPromptInputPriority{ 10 };

	UPROPERTY(EditDefaultsOnly, Category = "Input|MainMenuScreen")
	TObjectPtr<UMainMenuScreenInputMapping> MainMenuScreenInputMapping{ nullptr };
	UPROPERTY(EditDefaultsOnly, Category = "Input|MainMenuScreen")
	int32 MainMenuScreenInputPriority{ 10 };

	TObjectPtr<UProject1GameViewportClientBase> Project1GameViewportClient{ nullptr };
	FDelegateHandle OnMouseMovedDelegateHandle{};
	FDelegateHandle OnInputKeyDelegateHandle{};

public:
	void AddPressAnyInputPromptInputMappingContext();
	void RemovePressAnyInputPromptInputMappingContext();

	void AddMainMenuScreenInputMappingContext();
	void RemoveMainMenuScreenInputMappingContext();

private:
	void SetupInputComponent() override;
	void BeginPlay() override;
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void OnPressAnyInputPromptAnyInputTriggered(const FInputActionValue& Value);

	void OnMainMenuScreenConfirmTriggered(const FInputActionValue& Value);
	void OnMainMenuScreenNavigateTriggered(const FInputActionValue& Value);
};
