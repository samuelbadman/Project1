// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserWidgets/Project1UserWidgetBase.h"
#include "HelperObjects/WidgetLayerClassASyncLoadHandle.h"
#include "LayerUserWidgetBase.generated.h"

class UScreenUserWidgetBase;
class UPanelWidget;
struct FInputActionValue;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnContentPushedToLayerDelegateSignature, UScreenUserWidgetBase*, Widget);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnContentPoppedFromLayerDelegateSignature, UScreenUserWidgetBase*, Widget);

/**
 *
 */
UCLASS()
class PROJECT1_API ULayerUserWidgetBase : public UProject1UserWidgetBase
{
	GENERATED_BODY()

private:
	UPROPERTY(BlueprintAssignable)
	FOnContentPushedToLayerDelegateSignature OnContentPushedToLayerDelegate{};

	UPROPERTY(BlueprintAssignable)
	FOnContentPoppedFromLayerDelegateSignature OnContentPoppedFromLayerDelegate{};

	FGameplayTag LayerName{};

	UPROPERTY()
	TArray<TObjectPtr<UScreenUserWidgetBase>> WidgetStack{};
	
	UPROPERTY()
	TArray<TObjectPtr<UWidgetLayerClassASyncLoadHandle>> PushedContentClassASyncLoadHandles{};

public:
	UFUNCTION(BlueprintImplementableEvent)
	UPanelWidget* GetPanelWidget() const;

	void SetLayerName(const FGameplayTag& Name);
	void PushContent(const TSoftClassPtr<UScreenUserWidgetBase>& WidgetClass);
	void PopContent();
	TObjectPtr<UScreenUserWidgetBase> Peek() const;
	void CollapseTop();
	void ShowTop();
	bool IsEmpty() const;

	void OnLoadedPushedContentWidgetClass(TObjectPtr<UWidgetLayerClassASyncLoadHandle> Handle);

	void ReceiveOnMouseMoved(const FVector2D& NewMousePosition, const FVector2D& OldMousePosition, const FVector2D& MouseMoveDelta);
	void ReceiveOnLeftClickTriggered(const FInputActionValue& Value);
	void ReceiveOnMiddleClickTriggered(const FInputActionValue& Value);
	void ReceiveOnRightClickTriggered(const FInputActionValue& Value);
	void ReceiveOnMouseWheelTriggered(const FInputActionValue& Value);
	void ReceiveOnNavigateTriggered(const FInputActionValue& Value);
	void ReceiveOnConfirmTriggered(const FInputActionValue& Value);
	void ReceiveOnCancelTriggered(const FInputActionValue& Value);
	void ReceiveOnTabTriggered(const FInputActionValue& Value);
	void ReceiveOnAnyInputTriggered(const FInputActionValue& Value);
};
