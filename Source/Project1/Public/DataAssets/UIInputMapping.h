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
	UPROPERTY(EditDefaultsOnly, Category = "Mouse", meta = (DisplayName = "UI Mouse Input Mapping Context"))
	TObjectPtr<UInputMappingContext> UIMouseInputMappingContext{ nullptr };
	UPROPERTY(EditDefaultsOnly, Category = "Mouse", meta = (DisplayName = "UI Mouse Input Mapping Context Priority"))
	int32 UIMouseInputMappingContextPriority{ 0 };

	UPROPERTY(EditDefaultsOnly, Category = "Navigate", meta = (DisplayName = "UI Navigate Input Mapping Context"))
	TObjectPtr<UInputMappingContext> UINavigateInputMappingContext{ nullptr };
	UPROPERTY(EditDefaultsOnly, Category = "Navigate", meta = (DisplayName = "UI Navigate Input Mapping Context Priority"))
	int32 UINavigateInputMappingContextPriority{ 0 };

	UPROPERTY(EditDefaultsOnly, Category = "Navigate No Move", meta = (DisplayName = "UI Navigate No Move Input Mapping Context"))
	TObjectPtr<UInputMappingContext> UINavigateNoMoveInputMappingContext{ nullptr };
	UPROPERTY(EditDefaultsOnly, Category = "Navigate No Move", meta = (DisplayName = "UI Navigate No Move Input Mapping Context Priority"))
	int32 UINavigateNoMoveInputMappingContextPriority{ 0 };

	UPROPERTY(EditDefaultsOnly, Category = "Navigate No Move No Repeat", meta = (DisplayName = "UI Navigate No Move No Repeat Input Mapping Context"))
	TObjectPtr<UInputMappingContext> UINavigateNoMoveNoRepeatInputMappingContext{ nullptr };
	UPROPERTY(EditDefaultsOnly, Category = "Navigate No Move No Repeat", meta = (DisplayName = "UI Navigate No Move No Repeat Input Mapping Context Priority"))
	int32 UINavigateNoMoveNoRepeatInputMappingContextPriority{ 0 };

	UPROPERTY(EditDefaultsOnly, Category = "Confirm", meta = (DisplayName = "UI Confirm Input Mapping Context"))
	TObjectPtr<UInputMappingContext> UIConfirmInputMappingContext{ nullptr };
	UPROPERTY(EditDefaultsOnly, Category = "Confirm", meta = (DisplayName = "UI Confirm Input Mapping Context Priority"))
	int32 UIConfirmInputMappingContextPriority{ 0 };

	UPROPERTY(EditDefaultsOnly, Category = "Cancel", meta = (DisplayName = "UI Cancel Input Mapping Context"))
	TObjectPtr<UInputMappingContext> UICancelInputMappingContext{ nullptr };
	UPROPERTY(EditDefaultsOnly, Category = "Cancel", meta = (DisplayName = "UI Cancel Input Mapping Context Priority"))
	int32 UICancelInputMappingContextPriority{ 0 };

	UPROPERTY(EditDefaultsOnly, Category = "Tab", meta = (DisplayName = "UI Tab Input Mapping Context"))
	TObjectPtr<UInputMappingContext> UITabInputMappingContext{ nullptr };
	UPROPERTY(EditDefaultsOnly, Category = "Tab", meta = (DisplayName = "UI Tab Input Mapping Context Priority"))
	int32 UITabInputMappingContextPriority{ 0 };

	UPROPERTY(EditDefaultsOnly, Category = "Any Input", meta = (DisplayName = "UI Any Input Input Mapping Context"))
	TObjectPtr<UInputMappingContext> UIAnyInputInputMappingContext{ nullptr };
	UPROPERTY(EditDefaultsOnly, Category = "Any Input", meta = (DisplayName = "UI Any Input Input Mapping Context Priority"))
	int32 UIAnyInputInputMappingContextPriority{ 0 };

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
	TObjectPtr<UInputAction> NavigateNoMoveInputAction{ nullptr };

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> NavigateNoMoveNoRepeatInputAction{ nullptr };

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> ConfirmInputAction{ nullptr };

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> CancelInputAction{ nullptr };

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> TabInputAction{ nullptr };

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> AnyInputInputAction{ nullptr };

public:
	FORCEINLINE TObjectPtr<UInputMappingContext> GetUIMouseInputMappingContext() const { return UIMouseInputMappingContext; }
	FORCEINLINE int32 GetUIMouseInputMappingContextPriority() const { return UIMouseInputMappingContextPriority; }

	FORCEINLINE TObjectPtr<UInputMappingContext> GetUINavigateInputMappingContext() const { return UINavigateInputMappingContext; }
	FORCEINLINE int32 GetUINavigateInputMappingContextPriority() const { return UINavigateInputMappingContextPriority; }

	FORCEINLINE TObjectPtr<UInputMappingContext> GetUINavigateNoMoveInputMappingContext() const { return UINavigateNoMoveInputMappingContext; }
	FORCEINLINE int32 GetUINavigateNoMoveInputMappingContextPriority() const { return UINavigateNoMoveInputMappingContextPriority; }

	FORCEINLINE TObjectPtr<UInputMappingContext> GetUINavigateNoMoveNoRepeatInputMappingContext() const { return UINavigateNoMoveNoRepeatInputMappingContext; }
	FORCEINLINE int32 GetUINavigateNoMoveNoRepeatInputMappingContextPriority() const { return UINavigateNoMoveNoRepeatInputMappingContextPriority; }

	FORCEINLINE TObjectPtr<UInputMappingContext> GetUIConfirmInputMappingContext() const { return UIConfirmInputMappingContext; }
	FORCEINLINE int32 GetUIConfirmInputMappingContextPriority() const { return UIConfirmInputMappingContextPriority; }

	FORCEINLINE TObjectPtr<UInputMappingContext> GetUICancelInputMappingContext() const { return UICancelInputMappingContext; }
	FORCEINLINE int32 GetUICancelInputMappingContextPriority() const { return UICancelInputMappingContextPriority; }

	FORCEINLINE TObjectPtr<UInputMappingContext> GetUITabInputMappingContext() const { return UITabInputMappingContext; }
	FORCEINLINE int32 GetUITabInputMappingContextPriority() const { return UITabInputMappingContextPriority; }

	FORCEINLINE TObjectPtr<UInputMappingContext> GetUIAnyInputInputMappingContext() const { return UIAnyInputInputMappingContext; }
	FORCEINLINE int32 GetUIAnyInputInputMappingContextPriority() const { return UIAnyInputInputMappingContextPriority; }

	FORCEINLINE TObjectPtr<UInputAction> GetLeftClickInputAction() const { return LeftClickInputAction; }
	FORCEINLINE TObjectPtr<UInputAction> GetMiddleClickInputAction() const { return MiddleClickInputAction; }
	FORCEINLINE TObjectPtr<UInputAction> GetRightClickInputAction() const { return RightClickInputAction; }
	FORCEINLINE TObjectPtr<UInputAction> GetMouseWheelInputAction() const { return MouseWheelInputAction; }
	FORCEINLINE TObjectPtr<UInputAction> GetNavigateInputAction() const { return NavigateInputAction; }
	FORCEINLINE TObjectPtr<UInputAction> GetNavigateNoMoveInputAction() const { return NavigateNoMoveInputAction; }
	FORCEINLINE TObjectPtr<UInputAction> GetNavigateNoMoveNoRepeatInputAction() const { return NavigateNoMoveNoRepeatInputAction; }
	FORCEINLINE TObjectPtr<UInputAction> GetConfirmInputAction() const { return ConfirmInputAction; }
	FORCEINLINE TObjectPtr<UInputAction> GetCancelInputAction() const { return CancelInputAction; }
	FORCEINLINE TObjectPtr<UInputAction> GetTabInputAction() const { return TabInputAction; }
	FORCEINLINE TObjectPtr<UInputAction> GetAnyInputInputAction() const { return AnyInputInputAction; }
};
