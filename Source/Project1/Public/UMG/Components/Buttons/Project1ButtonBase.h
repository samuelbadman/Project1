// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG/Project1UserWidgetBase.h"
#include "Project1ButtonBase.generated.h"

class UImage;
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
	UPROPERTY(EditAnywhere)
	bool bStartActivated{ true };

	UPROPERTY(EditAnywhere)
	FSlateBrush NormalBrush{};

	UPROPERTY(EditAnywhere)
	FSlateBrush HoveredBrush{};

	UPROPERTY(EditAnywhere)
	FKey ClickKey{ EKeys::LeftMouseButton };

	UPROPERTY(EditAnywhere)
	bool bCanMouseUnhoverButton{ true };

	TObjectPtr<UProject1GameViewportClientBase> Project1GameViewportClient{ nullptr };
	FDelegateHandle OnMouseMovedDelegateHandle{};
	FDelegateHandle OnInputKeyDelegateHandle{};

	bool bActivated{ false };
	bool bHovered{ false };

public:
	UFUNCTION(BlueprintImplementableEvent)
	UImage* GetImage();

	void SetCanMouseUnhoverButton(bool CanMouseUnhoverButton) { bCanMouseUnhoverButton = CanMouseUnhoverButton; }

	void MakeHovered();
	void MakeUnhovered();
	void PressButton();

private:
	void NativePreConstruct() override;
	void NativeOnInitialized() override;
	void NativeDestruct() override;

	void Activate();
	void Deactivate();

	void OnMouseMoved(const FVector2D& NewMousePosition, const FVector2D& OldMousePosition, const FVector2D& MouseMoveDelta);
	void OnInputKey(const FInputKeyEventArgs& EventArgs);
};
