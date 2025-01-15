// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserWidgets/Project1UserWidgetBase.h"
#include "Project1ButtonWidgetBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPressedDelegateSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBecomeActiveDelegateSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEndActiveDelegateSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMouseEnteredGeometryDelegateSignature, UProject1ButtonWidgetBase*, Button);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMouseLeftGeometryDelegateSignature, UProject1ButtonWidgetBase*, Button);

class UProject1GameViewportClientBase;

/**
 * 
 */
UCLASS()
class PROJECT1_API UProject1ButtonWidgetBase : public UProject1UserWidgetBase
{
	GENERATED_BODY()
	
private:
	UPROPERTY(BlueprintAssignable, meta = (DisplayName = "On Button Pressed"))
	FOnPressedDelegateSignature OnPressedDelegate{};

	UPROPERTY(BlueprintAssignable, meta = (DisplayName = "On Button Become Active"))
	FOnBecomeActiveDelegateSignature OnBecomeActiveDelegate{};

	UPROPERTY(BlueprintAssignable, meta = (DisplayName = "On Button End Active"))
	FOnEndActiveDelegateSignature OnEndActiveDelegate{};

	UPROPERTY(BlueprintAssignable, meta = (DisplayName = "On Mouse Entered Button Geometry"))
	FOnMouseEnteredGeometryDelegateSignature OnMouseEnteredGeometryDelegate{};

	UPROPERTY(BlueprintAssignable, meta = (DisplayName = "On Mouse Left Button Geometry"))
	FOnMouseLeftGeometryDelegateSignature OnMouseLeftGeometryDelegate{};

	TObjectPtr<UProject1GameViewportClientBase> GameViewportClient{ nullptr };
	FDelegateHandle OnMouseMovedDelegateHandle{};
	bool bUnderMouse{ false };

public:
	UFUNCTION(BlueprintImplementableEvent)
	void OnPressed();

	UFUNCTION(BlueprintImplementableEvent)
	void OnBecomeActive();

	UFUNCTION(BlueprintImplementableEvent)
	void OnEndActive();

	UFUNCTION(BlueprintImplementableEvent)
	void OnMouseEnteredGeometry();

	UFUNCTION(BlueprintImplementableEvent)
	void OnMouseLeftGeometry();

	void MakeActive();
	void EndActive();
	void Press();

	FORCEINLINE FOnMouseEnteredGeometryDelegateSignature& GetOnMouseEnteredGeometryDelegate() { return OnMouseEnteredGeometryDelegate; }
	FORCEINLINE bool IsUnderMouse() const { return bUnderMouse; }

private:
	void BeginDestroy() override;
	void NativeOnInitialized() override;

	virtual void NativeOnPressed() {};
	virtual void NativeOnBecomeActive() {};
	virtual void NativeOnEndActive() {};
	virtual void NativeOnMouseEnteredGeomery() {};
	virtual void NativeOnMouseLeftGeomery() {};
};
