// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Controllers/PlayerControllers/Project1PlayerControllerBase.h"
#include "GameplayTagContainer.h"
#include "GamePlayerController.generated.h"

class AGamePlayerCameraManager;
class AGameHUD;
class UGameMenuScreen;
class UPlayerInteractComponent;
class UPlayerViewLockOnComponent;
class AProject1CharacterBase;
class AArtificialPlayerLight;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnInteractPromptInteractTriggeredDelegate, const FInputActionValue& /* Value */);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnInteractPromptSwitchActionTriggeredDelegate, const FInputActionValue& /* Value */);

DECLARE_MULTICAST_DELEGATE_OneParam(FOnDialogueScreenConfirmTriggeredDelegate, const FInputActionValue& /* Value */);

DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameMenuScreenConfirmTriggeredDelegate, const FInputActionValue& /* Value */);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameMenuScreenNavigateTriggeredDelegate, const FInputActionValue& /* Value */);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameMenuScreenCancelTriggeredDelegate, const FInputActionValue& /* Value */);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameMenuScreenQuitTriggeredDelegate, const FInputActionValue& /* Value */);

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

	FOnDialogueScreenConfirmTriggeredDelegate DialogueScreenConfirmTriggered{};

	FOnGameMenuScreenConfirmTriggeredDelegate GameMenuScreenConfirmTriggered{};
	FOnGameMenuScreenNavigateTriggeredDelegate GameMenuScreenNavigateTriggered{};
	FOnGameMenuScreenCancelTriggeredDelegate GameMenuScreenCancelTriggered{};
	FOnGameMenuScreenQuitTriggeredDelegate GameMenuScreenQuitTriggered{};

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPlayerInteractComponent> PlayerInteractComponent{ nullptr };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPlayerViewLockOnComponent> PlayerViewLockOnComponent{ nullptr };


	UPROPERTY(EditDefaultsOnly, Category = "GameInput|InteractPrompt")
	TObjectPtr<UInputMappingContext> InteractPromptInputMappingContext{ nullptr };

	UPROPERTY(EditDefaultsOnly, Category = "GameInput|InteractPrompt")
	int32 InteractPromptInputPriority{ 10 };

	UPROPERTY(EditDefaultsOnly, Category = "GameInput|InteractPrompt")
	TObjectPtr<UInputAction> InteractPromptInteractInputAction{ nullptr };

	UPROPERTY(EditDefaultsOnly, Category = "GameInput|InteractPrompt")
	TObjectPtr<UInputAction> InteractPromptSwitchActionInputAction{ nullptr };


	UPROPERTY(EditDefaultsOnly, Category = "GameInput|DialogueScreen")
	TObjectPtr<UInputMappingContext> DialogueScreenInputMappingContext{ nullptr };

	UPROPERTY(EditDefaultsOnly, Category = "GameInput|DialogueScreen")
	int32 DialogueScreenInputPriority{ 11 };

	UPROPERTY(EditDefaultsOnly, Category = "GameInput|DialogueScreen")
	TObjectPtr<UInputAction> DialogueScreenConfirmInputAction{ nullptr };


	UPROPERTY(EditDefaultsOnly, Category = "GameInput|GameMenuScreen")
	TObjectPtr<UInputMappingContext> GameMenuScreenInputMappingContext{ nullptr };

	UPROPERTY(EditDefaultsOnly, Category = "GameInput|GameMenuScreen")
	int32 GameMenuScreenInputPriority{ 0 };

	UPROPERTY(EditDefaultsOnly, Category = "GameInput|GameMenuScreen")
	TObjectPtr<UInputAction> GameMenuScreenConfirmInputAction{ nullptr };

	UPROPERTY(EditDefaultsOnly, Category = "GameInput|GameMenuScreen")
	TObjectPtr<UInputAction> GameMenuScreenNavigateInputAction{ nullptr };

	UPROPERTY(EditDefaultsOnly, Category = "GameInput|GameMenuScreen")
	TObjectPtr<UInputAction> GameMenuScreenCancelInputAction{ nullptr };

	UPROPERTY(EditDefaultsOnly, Category = "GameInput|GameMenuScreen")
	TObjectPtr<UInputAction> GameMenuScreenQuitInputAction{ nullptr };


	UPROPERTY(EditDefaultsOnly, Category = "GameInput|Look")
	TObjectPtr<UInputMappingContext> LookInputMappingContext{ nullptr };

	UPROPERTY(EditDefaultsOnly, Category = "GameInput|Look")
	int32 LookInputMappingContextPriority{ 0 };

	UPROPERTY(EditDefaultsOnly, Category = "GameInput|Look")
	TObjectPtr<UInputAction> LookAbsoluteInputAction{ nullptr };

	UPROPERTY(EditDefaultsOnly, Category = "GameInput|Look")
	TObjectPtr<UInputAction> LookAnalogInputAction{ nullptr };


	UPROPERTY(EditDefaultsOnly, Category = "GameInput|LookLockOn")
	TObjectPtr<UInputMappingContext> LookLockOnInputMappingContext{ nullptr };

	UPROPERTY(EditDefaultsOnly, Category = "GameInput|LookLockOn")
	int32 LookLockOnInputMappingContextPriority{ 0 };

	UPROPERTY(EditDefaultsOnly, Category = "GameInput|LookLockOn")
	TObjectPtr<UInputAction> LookLockOnInputAction{ nullptr };

	UPROPERTY(EditDefaultsOnly, Category = "GameInput|LookLockOn")
	TObjectPtr<UInputAction> SwitchLockTargetInputAction{ nullptr };


	UPROPERTY(EditDefaultsOnly, Category = "GameInput|ResetLook")
	TObjectPtr<UInputMappingContext> ResetLookInputMappingContext{ nullptr };

	UPROPERTY(EditDefaultsOnly, Category = "GameInput|ResetLook")
	int32 ResetLookInputMappingContextPriority{ 0 };

	UPROPERTY(EditDefaultsOnly, Category = "GameInput|ResetLook")
	TObjectPtr<UInputAction> ResetLookInputAction{ nullptr };


	UPROPERTY(EditDefaultsOnly, Category = "GameInput|Move")
	TObjectPtr<UInputMappingContext> MoveInputMappingContext{ nullptr };

	UPROPERTY(EditDefaultsOnly, Category = "GameInput|Move")
	int32 MoveInputMappingContextPriority{ 0 };

	UPROPERTY(EditDefaultsOnly, Category = "GameInput|Move")
	TObjectPtr<UInputAction> MoveInputAction{ nullptr };


	UPROPERTY(EditDefaultsOnly, Category = "GameInput|Jump")
	TObjectPtr<UInputMappingContext> JumpInputMappingContext{ nullptr };

	UPROPERTY(EditDefaultsOnly, Category = "GameInput|Jump")
	int32 JumpInputMappingContextPriority{ 0 };

	UPROPERTY(EditDefaultsOnly, Category = "GameInput|Jump")
	TObjectPtr<UInputAction> JumpInputAction{ nullptr };


	UPROPERTY(EditDefaultsOnly, Category = "GameInput|OpenGameMenu")
	TObjectPtr<UInputMappingContext> OpenGameMenuInputMappingContext{ nullptr };

	UPROPERTY(EditDefaultsOnly, Category = "GameInput|OpenGameMenu")
	int32 OpenGameMenuInputMappingContextPriority{ 0 };

	UPROPERTY(EditDefaultsOnly, Category = "GameInput|OpenGameMenu")
	TObjectPtr<UInputAction> OpenGameMenuInputAction{ nullptr };


	UPROPERTY(EditDefaultsOnly, Category = "GameInput|ToggleWalk")
	TObjectPtr<UInputMappingContext> ToggleWalkInputMappingContext{ nullptr };

	UPROPERTY(EditDefaultsOnly, Category = "GameInput|ToggleWalk")
	int32 ToggleWalkInputMappingContextPriority{ 0 };

	UPROPERTY(EditDefaultsOnly, Category = "GameInput|ToggleWalk")
	TObjectPtr<UInputAction> ToggleWalkInputAction{ nullptr };


	UPROPERTY(EditAnywhere, Category = "Look")
	FVector2D AbsoluteLookInputSensitivity{ 1.0, 1.0 };

	UPROPERTY(EditAnywhere, Category = "Look")
	FVector2D AnalogLookInputSensitivity{ 2.0, 2.0 };


	UPROPERTY(EditAnywhere, Category = "Move")
	float MoveRightViewYawRotationRate{ 25.0f };

	UPROPERTY(EditAnywhere, Category = "Move")
	float RunInputMagnitudeThreshold{ 0.5f };


	UPROPERTY(EditAnywhere, Category = "Player")
	TSoftClassPtr<AArtificialPlayerLight> ArtificialPlayerLightClass{ nullptr };

	TObjectPtr<UWorld> World{ nullptr };
	TObjectPtr<AGamePlayerCameraManager> GamePlayerCameraManager{ nullptr };
	TObjectPtr<AGameHUD> GameHUD{ nullptr };
	TObjectPtr<AProject1CharacterBase> PossessedCharacter{ nullptr };
	TObjectPtr<AArtificialPlayerLight> ArtificialPlayerLight{nullptr};
	bool bRestrictPlayerToWalk{ false };

public:
	AGamePlayerController();

	void AddInteractPromptInputMappingContext();
	void RemoveInteractPromptInputMappingContext();

	void AddDialogueScreenInputMappingContext();
	void RemoveDialogueScreenInputMappingContext();

	void AddGameMenuInputMappingContext();
	void RemoveGameMenuInputMappingContext();

	FORCEINLINE TObjectPtr<UPlayerInteractComponent> GetPlayerInteractComponent() const { return PlayerInteractComponent; }

private:
	void SetupInputComponent() override;
	void OnPossess(APawn* aPawn) override;
	void BeginPlay() override;

	void OnInteractPromptUIInteractTriggered(const FInputActionValue& Value);
	void OnInteractPromptUISwitchActionTriggered(const FInputActionValue& Value);

	void OnDialogueScreenConfirmTriggered(const FInputActionValue& Value);

	void OnGameMenuScreenConfirmTriggered(const FInputActionValue& Value);
	void OnGameMenuScreenNavigateTriggered(const FInputActionValue& Value);
	void OnGameMenuScreenCancelTriggered(const FInputActionValue& Value);
	void OnGameMenuScreenQuitTriggered(const FInputActionValue& Value);

	void OnLookAbsoluteTriggered(const FInputActionValue& Value);
	void OnLookAnalogTriggered(const FInputActionValue& Value);
	void OnResetLookTriggered(const FInputActionValue& Value);
	void OnMoveTriggered(const FInputActionValue& Value);
	void OnJumpTriggered(const FInputActionValue& Value);
	void OnOpenGameMenuTriggered(const FInputActionValue& Value);
	void OnLookLockOnTriggered(const FInputActionValue& Value);
	void OnSwitchLockTargetTriggered(const FInputActionValue& Value);
	void OnToggleWalkTriggered(const FInputActionValue& Value);
};
