// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Project1PlayerControllerBase.generated.h"

class UUIInputComponent;
class UUIInputBase;
class UEnhancedInputLocalPlayerSubsystem;

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMouseCursorVisibilityChangedDelegate, EMouseCursorVisibility /* NewVisibility */, const FVector2D& /* MousePosition */);

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
	FOnMouseCursorVisibilityChangedDelegate MouseCursorVisibilityChanged{};

private:
	UPROPERTY(EditDefaultsOnly)
	EMouseCursorVisibility DefaultMouseCursorVisibility{ EMouseCursorVisibility::Hidden };

	UPROPERTY(EditDefaultsOnly)
	bool DefaultLockMouseCursorToViewportWhenVisible{ false };

	UPROPERTY(EditDefaultsOnly)
	bool DefaultCenterCursorInViewportOnBecomeVisible{ true };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", DisplayName = "UI Input Component"))
	TObjectPtr<UUIInputComponent> UIInputComponent;

	TObjectPtr<UEnhancedInputLocalPlayerSubsystem> EnhancedInputLocalPlayerSubsystem{ nullptr };

public:
	AProject1PlayerControllerBase();

	UFUNCTION(BlueprintCallable, Category = "Project1PlayerController")
	void SetMouseCursorVisibility(EMouseCursorVisibility NewVisibility, bool LockMouseCursorToViewportWhenVisible, bool CenterCursorInViewportOnBecomeVisible);

	UFUNCTION(BlueprintCallable, Category = "Project1PlayerController")
	EMouseCursorVisibility GetMouseCursorVisibility() const;

	UFUNCTION(BlueprintCallable, Category = "Project1PlayerController")
	FVector2D GetMouseCursorPosition() const;

	UFUNCTION(BlueprintCallable)
	bool IsMouseCursorVisible() const { return bShowMouseCursor; }

	FORCEINLINE TObjectPtr<UEnhancedInputLocalPlayerSubsystem> GetEnhancedInputLocalPlayerSubsystem() const { return EnhancedInputLocalPlayerSubsystem; }
	FORCEINLINE TObjectPtr<UUIInputComponent> GetUIInputComponent() const { return UIInputComponent; }

protected:
	void SetupInputComponent() override;
	void BeginPlay() override;

	virtual void OnMouseCursorVisibilityChanged(EMouseCursorVisibility NewVisibility);

private:
	void CenterMouseCursorInViewport();
};
