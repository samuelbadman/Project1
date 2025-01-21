// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerControllers/Project1PlayerControllerBase.h"
#include "GameplayTagContainer.h"
#include "GamePlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UPlayerCharacterControllerComponent;
class AGamePlayerCameraManager;
class UPlayerInteractComponent;
class AProject1HUDBase;

/**
 *
 */
UCLASS()
class PROJECT1_API AGamePlayerController : public AProject1PlayerControllerBase
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPlayerCharacterControllerComponent> PlayerCharacterControllerComponent{ nullptr };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPlayerInteractComponent> PlayerInteractComponent{ nullptr };

	UPROPERTY(EditDefaultsOnly, Category = "Input|LookInputs")
	TObjectPtr<UInputMappingContext> LookInputMappingContext{ nullptr };
	UPROPERTY(EditDefaultsOnly, Category = "Input|LookInputs")
	int32 LookInputMappingContextPriority{ 0 };
	UPROPERTY(EditDefaultsOnly, Category = "Input|LookInputs")
	TObjectPtr<UInputAction> LookAbsoluteInputAction{ nullptr };
	UPROPERTY(EditDefaultsOnly, Category = "Input|LookInputs")
	TObjectPtr<UInputAction> LookAnalogInputAction{ nullptr };

	UPROPERTY(EditDefaultsOnly, Category = "Input|ResetLookInputs")
	TObjectPtr<UInputMappingContext> ResetLookInputMappingContext{ nullptr };
	UPROPERTY(EditDefaultsOnly, Category = "Input|ResetLookInputs")
	int32 ResetLookInputMappingContextPriority{ 0 };
	UPROPERTY(EditDefaultsOnly, Category = "Input|ResetLookInputs")
	TObjectPtr<UInputAction> ResetLookInputAction{ nullptr };

	UPROPERTY(EditDefaultsOnly, Category = "Input|MoveInputs")
	TObjectPtr<UInputMappingContext> MoveInputMappingContext{ nullptr };
	UPROPERTY(EditDefaultsOnly, Category = "Input|MoveInputs")
	int32 MoveInputMappingContextPriority{ 0 };
	UPROPERTY(EditDefaultsOnly, Category = "Input|MoveInputs")
	TObjectPtr<UInputAction> MoveInputAction{ nullptr };

	UPROPERTY(EditDefaultsOnly, Category = "Input|JumpInputs")
	TObjectPtr<UInputMappingContext> JumpInputMappingContext{ nullptr };
	UPROPERTY(EditDefaultsOnly, Category = "Input|JumpInputs")
	int32 JumpInputMappingContextPriority{ 0 };
	UPROPERTY(EditDefaultsOnly, Category = "Input|JumpInputs")
	TObjectPtr<UInputAction> JumpInputAction{ nullptr };

	UPROPERTY(EditAnywhere, Category = "LookSensitivitySettings")
	FVector2D AbsoluteLookInputSensitivity{ 1.0, 1.0 };

	UPROPERTY(EditAnywhere, Category = "LookSensitivitySettings")
	FVector2D AnalogLookInputSensitivity{ 2.0, 2.0 };

	UPROPERTY(EditAnywhere, Category = "Move")
	float MoveRightViewYawRotationRate{ 25.0f };

	UPROPERTY(EditDefaultsOnly, Category = "Interact")
	FGameplayTag InteractPromptWidgetLayerName{};

	TObjectPtr<UWorld> World{ nullptr };
	TObjectPtr<AGamePlayerCameraManager> GamePlayerCameraManager{ nullptr };
	TObjectPtr<AProject1HUDBase> Project1HUD{ nullptr };

public:
	AGamePlayerController();

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

	void OnInteractableBeginPlayerOverlap(TWeakObjectPtr<AActor> Interactable, int32 NumOverlappedInteractables);
	void OnInteractableEndPlayerOverlap(TWeakObjectPtr<AActor> Interactable, int32 NumOverlappedInteractables);
};
