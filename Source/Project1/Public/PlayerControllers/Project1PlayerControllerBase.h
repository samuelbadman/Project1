// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Project1PlayerControllerBase.generated.h"

class UEnhancedInputLocalPlayerSubsystem;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

// Inputs that are used by multiple player controllers need to be set up in the project's base player controller class

DECLARE_MULTICAST_DELEGATE_OneParam(FOnConfirmModalConfirmTriggeredDelegate, const FInputActionValue& /* Value */);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnConfirmModalNavigateTriggeredDelegate, const FInputActionValue& /* Value */);

DECLARE_MULTICAST_DELEGATE_OneParam(FOnDynamicModalConfirmTriggeredDelegate, const FInputActionValue& /* Value */);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnDynamicModalNavigateTriggeredDelegate, const FInputActionValue& /* Value */);

UENUM()
enum class EMouseCursorVisibility : uint8
{
	Visible,
	Hidden
};

/**
 * 
 */
UCLASS()
class PROJECT1_API AProject1PlayerControllerBase : public APlayerController
{
	GENERATED_BODY()
	
public:
	FOnConfirmModalConfirmTriggeredDelegate ConfirmModalConfirmTriggered{};
	FOnConfirmModalNavigateTriggeredDelegate ConfirmModalNavigateTriggered{};

	FOnDynamicModalConfirmTriggeredDelegate DynamicModalConfirmTriggered{};
	FOnDynamicModalNavigateTriggeredDelegate DynamicModalNavigateTriggered{};

private:
	UPROPERTY(EditDefaultsOnly)
	EMouseCursorVisibility DefaultMouseCursorVisibility{ EMouseCursorVisibility::Hidden };

	UPROPERTY(EditDefaultsOnly)
	bool DefaultLockMouseCursorToViewportWhenVisible{ false };

	UPROPERTY(EditDefaultsOnly)
	bool DefaultCenterCursorInViewportOnBecomeVisible{ true };

	UPROPERTY(EditDefaultsOnly, Category = "Input|ConfirmModal")
	TObjectPtr<UInputMappingContext> ConfirmModalInputMappingContext{ nullptr };

	UPROPERTY(EditDefaultsOnly, Category = "Input|ConfirmModal")
	int32 ConfirmModalInputPriority{ 15 };

	UPROPERTY(EditDefaultsOnly, Category = "Input|ConfirmModal")
	TObjectPtr<UInputAction> ConfirmModalConfirmInputAction{ nullptr };

	UPROPERTY(EditDefaultsOnly, Category = "Input|ConfirmModal")
	TObjectPtr<UInputAction> ConfirmModalNavigateInputAction{ nullptr };

	UPROPERTY(EditDefaultsOnly, Category = "Input|DynamicModal")
	TObjectPtr<UInputMappingContext> DynamicModalInputMappingContext{ nullptr };

	UPROPERTY(EditDefaultsOnly, Category = "Input|DynamicModal")
	int32 DynamicModalInputPriority{ 15 };

	UPROPERTY(EditDefaultsOnly, Category = "Input|DynamicModal")
	TObjectPtr<UInputAction> DynamicModalConfirmInputAction{ nullptr };

	UPROPERTY(EditDefaultsOnly, Category = "Input|DynamicModal")
	TObjectPtr<UInputAction> DynamicModalNavigateInputAction{ nullptr };

public:
	UFUNCTION(BlueprintCallable)
	void SetMouseCursorVisibility(EMouseCursorVisibility NewVisibility, bool LockMouseCursorToViewportWhenVisible, bool CenterCursorInViewportOnBecomeVisible);

	UFUNCTION(BlueprintCallable)
	bool IsMouseCursorVisible() const { return bShowMouseCursor; }

	void AddConfirmModalInputMappingContext();
	void RemoveConfirmModalInputMappingContext();

	void AddDynamicModalInputMappingContext();
	void RemoveDynamicModalInputMappingContext();

protected:
	void SetupInputComponent() override;
	void BeginPlay() override;

	virtual void OnMouseCursorVisibilityChanged(EMouseCursorVisibility NewVisibility) {};

	// Returns the enhanced input local player subsystem for the local player. Can return null if the local player for this controller does not exist
	TObjectPtr<UEnhancedInputLocalPlayerSubsystem> GetEnhancedInputLocalPlayerSubsystem() const;

private:
	void CenterMouseCursorInViewport();

	void OnConfirmModalConfirmTriggered(const FInputActionValue& Value);
	void OnConfirmModalNavigateTriggered(const FInputActionValue& Value);	
	
	void OnDynamicModalConfirmTriggered(const FInputActionValue& Value);
	void OnDynamicModalNavigateTriggered(const FInputActionValue& Value);
};
