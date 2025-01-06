// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UIInputMapping.generated.h"

class UInputMappingContext;
class UInputAction;

/**
 * 
 */
UCLASS()
class PROJECT1_API UUIInputMapping : public UDataAsset
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly, meta = (DisplayName = "UI Input Mapping Context"))
	TObjectPtr<UInputMappingContext> UIInputMappingContext{ nullptr };

	UPROPERTY(EditDefaultsOnly)
	int32 UIInputMappingContextPriority{ 0 };

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> LeftClickInputAction{ nullptr };

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> MiddleClickInputAction{ nullptr };

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> RightClickInputAction{ nullptr };

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> MouseWheelInputAction{ nullptr };

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> NavigateInputAction{ nullptr };

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> ConfirmInputAction{ nullptr };

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> CancelInputAction{ nullptr };

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> TabInputAction{ nullptr };

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> AnyInputInputAction{ nullptr };

public:
	FORCEINLINE TObjectPtr<UInputMappingContext> GetUIInputMappingContext() const { return UIInputMappingContext; }
	FORCEINLINE int32 GetUIInputMappingContextPriority() const { return UIInputMappingContextPriority; }
	FORCEINLINE TObjectPtr<UInputAction> GetLeftClickInputAction() const { return LeftClickInputAction; }
	FORCEINLINE TObjectPtr<UInputAction> GetMiddleClickInputAction() const { return MiddleClickInputAction; }
	FORCEINLINE TObjectPtr<UInputAction> GetRightClickInputAction() const { return RightClickInputAction; }
	FORCEINLINE TObjectPtr<UInputAction> GetMouseWheelInputAction() const { return MouseWheelInputAction; }
	FORCEINLINE TObjectPtr<UInputAction> GetNavigateInputAction() const { return NavigateInputAction; }
	FORCEINLINE TObjectPtr<UInputAction> GetConfirmInputAction() const { return ConfirmInputAction; }
	FORCEINLINE TObjectPtr<UInputAction> GetCancelInputAction() const { return CancelInputAction; }
	FORCEINLINE TObjectPtr<UInputAction> GetTabInputAction() const { return TabInputAction; }
	FORCEINLINE TObjectPtr<UInputAction> GetAnyInputInputAction() const { return AnyInputInputAction; }
};
