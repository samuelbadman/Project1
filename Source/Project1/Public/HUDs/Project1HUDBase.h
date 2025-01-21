// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Project1HUDBase.generated.h"

class UPrimaryLayoutUserWidgetBase;
struct FGameplayTag;
class UScreenUserWidgetBase;
class ULayerUserWidgetBase;
struct FInputActionValue;
class UEnhancedInputComponent;
class UUIInputMapping;
class UProject1GameViewportClientBase;

/**
 *
 */
UCLASS()
class PROJECT1_API AProject1HUDBase : public AHUD
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UUIInputMapping> UIInputMapping{ nullptr };

	UPROPERTY(EditDefaultsOnly, Category = "PrimaryWidgetLayout")
	TSubclassOf<UPrimaryLayoutUserWidgetBase> PrimaryLayoutWidgetClass{ nullptr };

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPrimaryLayoutUserWidgetBase> PrimaryLayoutWidget{ nullptr };

	FDelegateHandle OnMouseMovedDelegateHandle{};

public:
	void PushContentToPrimaryLayoutLayer(const FGameplayTag& LayerName, const TSoftClassPtr<UScreenUserWidgetBase>& WidgetClass);
	void PopContentFromPrimaryLayoutLayer(const FGameplayTag& LayerName);
	ULayerUserWidgetBase* GetRegisteredPrimaryLayoutLayer(const FGameplayTag& LayerName);
	void SetActiveInputPrimaryLayoutLayer(const FGameplayTag& LayerName);
	const FGameplayTag& GetPreviousActiveInputPrimaryLayoutLayer() const;
	bool IsContentOnTopOfPrimaryLayoutLayer(const FGameplayTag& LayerName, TObjectPtr<UScreenUserWidgetBase> Widget) const;

	void BindUIInputActions(UEnhancedInputComponent* EnhancedInputComponent);
	void BindToMouseMoveEvents(UProject1GameViewportClientBase* Project1GameViewportClient);
	void UnbindFromMouseMoveEvents(UProject1GameViewportClientBase* Project1GameViewportClient);

	FORCEINLINE TObjectPtr<UUIInputMapping> GetUIInputMapping() const { return UIInputMapping; }

protected:
	void BeginPlay() override;

private:
	void OnMouseMoved(const FVector2D& NewMousePosition, const FVector2D& OldMousePosition, const FVector2D& MouseMoveDelta);
	void OnLeftClickTriggered(const FInputActionValue& Value);
	void OnMiddleClickTriggered(const FInputActionValue& Value);
	void OnRightClickTriggered(const FInputActionValue& Value);
	void OnMouseWheelTriggered(const FInputActionValue& Value);
	void OnNavigateTriggered(const FInputActionValue& Value);
	void OnNavigateNoMoveTriggered(const FInputActionValue& Value);
	void OnNavigateNoMoveNoRepeatTriggered(const FInputActionValue& Value);
	void OnConfirmTriggered(const FInputActionValue& Value);
	void OnCancelTriggered(const FInputActionValue& Value);
	void OnTabTriggered(const FInputActionValue& Value);
	void OnAnyInputTriggered(const FInputActionValue& Value);
};
