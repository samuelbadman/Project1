// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG/Project1UserWidgetBase.h"
#include "Project1ButtonBase.generated.h"

class UBorder;
class AProject1PlayerControllerBase;
class UProject1GameViewportClientBase;
enum class EMouseCursorVisibility : uint8;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHoveredDelegate, UProject1ButtonBase*, ButtonHovered);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUnhoveredDelegate, UProject1ButtonBase*, ButtonUnhovered);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnClickedDelegate, UProject1ButtonBase*, ButtonClicked);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPressedDelegate, UProject1ButtonBase*, ButtonPressed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMouseCursorOverDelegate, UProject1ButtonBase*, ButtonOver);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMouseCursorLeftDelegate, UProject1ButtonBase*, ButtonLeft);

/**
 * 
 */
UCLASS()
class PROJECT1_API UProject1ButtonBase : public UProject1UserWidgetBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable)
	FOnHoveredDelegate OnHovered{};

	UPROPERTY(BlueprintAssignable)
	FOnUnhoveredDelegate OnUnhovered{};

	UPROPERTY(BlueprintAssignable)
	FOnClickedDelegate OnClicked{};

	UPROPERTY(BlueprintAssignable)
	FOnPressedDelegate OnPressed{};

	UPROPERTY(BlueprintAssignable)
	FOnMouseCursorOverDelegate OnMouseCursorOver{};

	UPROPERTY(BlueprintAssignable)
	FOnMouseCursorLeftDelegate OnMouseCursorLeft{};

private:
	// Brush applied to the button image when it is in an unhovered state
	UPROPERTY(EditAnywhere)
	FSlateBrush NormalBrush{};

	// Brush applied to the button image when it is in a hovered state
	UPROPERTY(EditAnywhere)
	FSlateBrush HoveredBrush{};

	// Toggles whether the button becomes hovered when the mouse cursor moves over and leaves the button widget's geometry. When this is false, it is expected code using the button
	// will manage the button's hovered state. For an example of this see ButtonMenuComponent
	bool bGenerateHoverEvents{ true };

	// The key that generates button click events when pressed and the mouse cursor is over the button widget's geometry
	UPROPERTY(EditAnywhere)
	FKey ClickKey{ EKeys::LeftMouseButton };

	UPROPERTY(EditAnywhere)
	FMargin ContentPadding{};

	TObjectPtr<AProject1PlayerControllerBase> Project1PlayerController{ nullptr };
	TObjectPtr<UProject1GameViewportClientBase> Project1GameViewportClient{ nullptr };
	FDelegateHandle OnMouseCursorVisibilityChangedDelegateHandle{};
	FDelegateHandle OnMouseMovedDelegateHandle{};
	FDelegateHandle OnInputKeyDelegateHandle{};

	bool bMouseInputsActivated{ false };
	bool bLastMouseInputsActivated{ false }; // Used to determine whether mouse inputs were activated when NativeDestruct was last called on the button
	bool bHovered{ false };
	bool bCursorOver{ false };

public:
	UFUNCTION(BlueprintImplementableEvent)
	UBorder* GetBorder();

	// Activates the button allowing it to handle mouse cursor events
	UFUNCTION(BlueprintCallable, Category = "Project1ButtonBase")
	void ActivateMouseInput();
	// Deactivates the button stopping it from handling mouse cursor events
	UFUNCTION(BlueprintCallable, Category = "Project1ButtonBase")
	void DeactivateMouseInput();

	// Puts the button into a hovered state
	void MakeHovered();
	// Puts the button into an unhovered state
	void MakeUnhovered();

	void PressButton();

	FORCEINLINE bool AreMouseInputsActivated() const { return bMouseInputsActivated; }
	FORCEINLINE bool IsHovered() const { return bHovered; }
	FORCEINLINE void SetGenerateHoverEvents(const bool NewGenerateHoverEvents) { bGenerateHoverEvents = NewGenerateHoverEvents; }

private:
	void NativePreConstruct() override;
	void NativeOnInitialized() override;
	void NativeDestruct() override;

	void OnMouseCursorVisibilityChanged(EMouseCursorVisibility NewVisibility, const FVector2D& MousePosition);
	void OnMouseMoved(const FVector2D& NewMousePosition, const FVector2D& OldMousePosition, const FVector2D& MouseMoveDelta);
	void OnInputKey(const FInputKeyEventArgs& EventArgs);

	void OnMouseCursorOverWidget();
	void OnMouseCursorLeftWidget();
};
