// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG/Project1UserWidgetBase.h"
#include "Project1ButtonBase.generated.h"

class UImage;
class AProject1PlayerControllerBase;
class UProject1GameViewportClientBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHoveredDelegate, UProject1ButtonBase*, ButtonHovered);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUnhoveredDelegate, UProject1ButtonBase*, ButtonUnhovered);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnClickedDelegate, UProject1ButtonBase*, ButtonClicked);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPressedDelegate, UProject1ButtonBase*, ButtonPressed);

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

private:
	// Whether to activate the button automatically during its start
	UPROPERTY(EditAnywhere)
	bool bStartActivated{ true };

	// Brush applied to the button image when it is in an unhovered state
	UPROPERTY(EditAnywhere)
	FSlateBrush NormalBrush{};

	// Brush applied to the button image when it is in a hovered state
	UPROPERTY(EditAnywhere)
	FSlateBrush HoveredBrush{};

	// The key that generates button click events when pressed and the mouse cursor is over the button widget's geometry
	UPROPERTY(EditAnywhere)
	FKey ClickKey{ EKeys::LeftMouseButton };

	// Controls whether an unhover event will be generated when the mouse cursor leaves the button widget's geometry. Can be useful when it is desired for a screen 
	// to manage button hover state
	UPROPERTY(EditAnywhere)
	bool bCanMouseUnhoverButton{ true };

	TObjectPtr<AProject1PlayerControllerBase> Project1PlayerController{ nullptr };
	TObjectPtr<UProject1GameViewportClientBase> Project1GameViewportClient{ nullptr };
	FDelegateHandle OnMouseMovedDelegateHandle{};
	FDelegateHandle OnInputKeyDelegateHandle{};

	bool bActivated{ false };
	bool bHovered{ false };

public:
	UFUNCTION(BlueprintImplementableEvent)
	UImage* GetImage();

	void SetCanMouseUnhoverButton(bool CanMouseUnhoverButton) { bCanMouseUnhoverButton = CanMouseUnhoverButton; }

	// Puts the button into a hovered state
	void MakeHovered();
	// Puts the button into an unhovered state
	void MakeUnhovered();

	void PressButton();

	FORCEINLINE bool IsActivated() const { return bActivated; }
	FORCEINLINE bool IsHovered() const { return bHovered; }

private:
	void NativePreConstruct() override;
	void NativeOnInitialized() override;
	void NativeDestruct() override;

	// Activates the button allowing it to handle to mouse cursor events
	void Activate();
	// Deactivates the button stopping it from handling mouse cursor events
	void Deactivate();

	void OnMouseMoved(const FVector2D& NewMousePosition, const FVector2D& OldMousePosition, const FVector2D& MouseMoveDelta);
	void OnInputKey(const FInputKeyEventArgs& EventArgs);
};
