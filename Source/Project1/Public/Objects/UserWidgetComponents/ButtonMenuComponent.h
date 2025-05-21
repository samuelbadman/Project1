// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserWidgetComponent.h"
#include "ButtonMenuComponent.generated.h"

class UProject1ButtonBase;
enum class EWidgetNavigationDirection : uint8;

/**
 *
 */
UCLASS()
class PROJECT1_API UButtonMenuComponent : public UUserWidgetComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	bool bFocusButtonOnMouseCursorEnter;

	UPROPERTY(EditAnywhere)
	bool bUnfocusButtonOnMouseCursorLeave;

	TArray<TObjectPtr<UProject1ButtonBase>> RegisteredButtons;
	TObjectPtr<UProject1ButtonBase> FocusedButton;
	int32 FocusedButtonIndex;

public:
	UButtonMenuComponent();

	// Registers menu buttons with the component. Subsequent calls of this function will append buttons to the component keeping any previously registered buttons.
	// When navigating the menu using an index offset, the order buttons appear in the array being registered in is important as this is the order the buttons will
	// be navigated in
	UFUNCTION(BlueprintCallable, Category = "ButtonMenuComponent")
	void RegisterMenuButtons(const TArray<UProject1ButtonBase*>& Buttons, bool ActivateButtonMouseInput);

	// Focuses the button in the menu if the button has been registered with the menu
	UFUNCTION(BlueprintCallable, Category = "ButtonMenuComponent")
	void FocusButton(UProject1ButtonBase* Button);

	UFUNCTION(BlueprintCallable, Category = "ButtonMenuComponent")
	FORCEINLINE void SetFocusButtonOnMouseCursorEnter(bool Focus) { bFocusButtonOnMouseCursorEnter = Focus; }

	UFUNCTION(BlueprintCallable, Category = "ButtonMenuComponent")
	FORCEINLINE void SetUnfocusButtonOnMouseCursorLeave(bool Unfocus) { bUnfocusButtonOnMouseCursorLeave = Unfocus; }

	// Returns the widget navigated to if there is one otherwise, returns null. Null is a valid return value as this means that there was no navigation
	TObjectPtr<UProject1ButtonBase> NavigateMenu(const EWidgetNavigationDirection Direction);
	// Returns the widget navigated to if there is one otherwise, returns null. Null is a valid return value as this means that there was no navigation
	TObjectPtr<UProject1ButtonBase> NavigateMenu(int32 Amount, bool Wrap);
	void PressFocusedButton();

	UFUNCTION(BlueprintCallable, Category = "ButtonMenuComponent")
	FORCEINLINE UProject1ButtonBase* GetFocusedButton() const { return FocusedButton; }
	UFUNCTION(BlueprintCallable, Category = "ButtonMenuComponent")
	int32 GetNumRegisteredButtons() const { return RegisteredButtons.Num(); }

private:
	UFUNCTION()
	void OnMouseCursorOverMenuButton(UProject1ButtonBase* Button);
	UFUNCTION()
	void OnMouseCursorLeftMenuButton(UProject1ButtonBase* Button);
};
