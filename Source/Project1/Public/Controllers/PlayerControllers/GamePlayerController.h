// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Controllers/PlayerControllers/Project1PlayerControllerBase.h"
#include "GamePlayerController.generated.h"

class AGamePlayerCameraManager;
class AGameHUD;
class UGameMenuScreen;
class UPlayerInteractComponent;
class UPlayerViewLockOnComponent;
class AProject1CharacterBase;
class AArtificialPlayerLight;
struct FInputActionValue;
class UInputMappingContext;
class UInputAction;

/**
 *
 */
UCLASS()
class PROJECT1_API AGamePlayerController : public AProject1PlayerControllerBase
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPlayerInteractComponent> PlayerInteractComponent{ nullptr };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPlayerViewLockOnComponent> PlayerViewLockOnComponent{ nullptr };

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
	bool bLimitPlayerToWalk{ false };

public:
	AGamePlayerController();

	void ActivateArtificialPlayerLight(bool Activate);

	FORCEINLINE TObjectPtr<UPlayerInteractComponent> GetPlayerInteractComponent() const { return PlayerInteractComponent; }

private:
	void SetupInputComponent() override;
	void OnPossess(APawn* aPawn) override;
	void BeginPlay() override;

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
