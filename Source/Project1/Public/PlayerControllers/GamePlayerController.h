// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerControllers/Project1PlayerControllerBase.h"
#include "GameplayTagContainer.h"
#include "GamePlayerController.generated.h"

class AGamePlayerCameraManager;
class UPlayerCharacterControllerComponent;
class UPlayerInteractComponent;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnInteractPromptInteractTriggeredDelegate, const FInputActionValue& /* Value */);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnInteractPromptSwitchActionTriggeredDelegate, const FInputActionValue& /* Value */);

DECLARE_MULTICAST_DELEGATE_OneParam(FOnDialogueScreenConfirmTriggered, const FInputActionValue& /* Value */);

/**
 *
 */
UCLASS()
class PROJECT1_API AGamePlayerController : public AProject1PlayerControllerBase
{
	GENERATED_BODY()

public:
	FOnInteractPromptInteractTriggeredDelegate InteractPromptInteractTriggered{};
	FOnInteractPromptSwitchActionTriggeredDelegate InteractPromptSwitchActionTriggered{};

	FOnDialogueScreenConfirmTriggered DialogueScreenConfirmTriggered{};

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPlayerCharacterControllerComponent> PlayerCharacterControllerComponent{ nullptr };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPlayerInteractComponent> PlayerInteractComponent{ nullptr };

	UPROPERTY(EditDefaultsOnly, Category = "Input|InteractPrompt")
	TObjectPtr<UInputMappingContext> InteractPromptInputMappingContext{ nullptr };

	UPROPERTY(EditDefaultsOnly, Category = "Input|InteractPrompt")
	int32 InteractPromptInputPriority{ 10 };

	UPROPERTY(EditDefaultsOnly, Category = "Input|InteractPrompt")
	TObjectPtr<UInputAction> InteractPromptInteractInputAction{ nullptr };

	UPROPERTY(EditDefaultsOnly, Category = "Input|InteractPrompt")
	TObjectPtr<UInputAction> InteractPromptSwitchActionInputAction{ nullptr };

	UPROPERTY(EditDefaultsOnly, Category = "Input|DialogueScreen")
	TObjectPtr<UInputMappingContext> DialogueScreenInputMappingContext{ nullptr };

	UPROPERTY(EditDefaultsOnly, Category = "Input|DialogueScreen")
	int32 DialogueScreenInputPriority{ 11 };

	UPROPERTY(EditDefaultsOnly, Category = "Input|DialogueScreen")
	TObjectPtr<UInputAction> DialogueScreenConfirmInputAction{ nullptr };

	UPROPERTY(EditDefaultsOnly, Category = "Input|Look")
	TObjectPtr<UInputMappingContext> LookInputMappingContext{ nullptr };

	UPROPERTY(EditDefaultsOnly, Category = "Input|Look")
	int32 LookInputMappingContextPriority{ 0 };

	UPROPERTY(EditDefaultsOnly, Category = "Input|Look")
	TObjectPtr<UInputAction> LookAbsoluteInputAction{ nullptr };

	UPROPERTY(EditDefaultsOnly, Category = "Input|Look")
	TObjectPtr<UInputAction> LookAnalogInputAction{ nullptr };

	UPROPERTY(EditDefaultsOnly, Category = "Input|ResetLook")
	TObjectPtr<UInputMappingContext> ResetLookInputMappingContext{ nullptr };

	UPROPERTY(EditDefaultsOnly, Category = "Input|ResetLook")
	int32 ResetLookInputMappingContextPriority{ 0 };

	UPROPERTY(EditDefaultsOnly, Category = "Input|ResetLook")
	TObjectPtr<UInputAction> ResetLookInputAction{ nullptr };

	UPROPERTY(EditDefaultsOnly, Category = "Input|Move")
	TObjectPtr<UInputMappingContext> MoveInputMappingContext{ nullptr };

	UPROPERTY(EditDefaultsOnly, Category = "Input|Move")
	int32 MoveInputMappingContextPriority{ 0 };

	UPROPERTY(EditDefaultsOnly, Category = "Input|Move")
	TObjectPtr<UInputAction> MoveInputAction{ nullptr };

	UPROPERTY(EditDefaultsOnly, Category = "Input|Jump")
	TObjectPtr<UInputMappingContext> JumpInputMappingContext{ nullptr };

	UPROPERTY(EditDefaultsOnly, Category = "Input|Jump")
	int32 JumpInputMappingContextPriority{ 0 };

	UPROPERTY(EditDefaultsOnly, Category = "Input|Jump")
	TObjectPtr<UInputAction> JumpInputAction{ nullptr };

	UPROPERTY(EditAnywhere, Category = "LookSensitivitySettings")
	FVector2D AbsoluteLookInputSensitivity{ 1.0, 1.0 };

	UPROPERTY(EditAnywhere, Category = "LookSensitivitySettings")
	FVector2D AnalogLookInputSensitivity{ 2.0, 2.0 };

	UPROPERTY(EditAnywhere, Category = "MoveSettings")
	float MoveRightViewYawRotationRate{ 25.0f };

	TObjectPtr<UWorld> World{ nullptr };
	TObjectPtr<AGamePlayerCameraManager> GamePlayerCameraManager{ nullptr };

public:
	AGamePlayerController();

	void AddInteractPromptInputMappingContext();
	void RemoveInteractPromptInputMappingContext();

	void AddDialogueScreenInputMappingContext();
	void RemoveDialogueScreenInputMappingContext();

	FORCEINLINE TObjectPtr<UPlayerInteractComponent> GetPlayerInteractComponent() const { return PlayerInteractComponent; }

private:
	void SetupInputComponent() override;
	void OnPossess(APawn* aPawn) override;
	void BeginPlay() override;

	void OnInteractPromptUIInteractTriggered(const FInputActionValue& Value);
	void OnInteractPromptUISwitchActionTriggered(const FInputActionValue& Value);

	void OnDialogueScreenConfirmTriggered(const FInputActionValue& Value);

	void OnLookAbsoluteTriggered(const FInputActionValue& Value);
	void OnLookAnalogTriggered(const FInputActionValue& Value);
	void OnResetLookTriggered(const FInputActionValue& Value);
	void OnMoveTriggered(const FInputActionValue& Value);
	void OnJumpTriggered(const FInputActionValue& Value);
};
