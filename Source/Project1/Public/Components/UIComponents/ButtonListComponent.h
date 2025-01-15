// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/UIComponents/UIComponentBase.h"
#include "ButtonListComponent.generated.h"

class UProject1ButtonWidgetBase;

/**
 *
 */
UCLASS()
class PROJECT1_API UButtonListComponent : public UUIComponentBase
{
	GENERATED_BODY()

private:
	TArray<TObjectPtr<UProject1ButtonWidgetBase>> RegisteredButtons{};
	int32 ActiveButtonIndex{ INDEX_NONE };

public:
	UFUNCTION(BlueprintCallable)
	void RegisterButtons(const TArray<UProject1ButtonWidgetBase*>& Buttons, int32 NewActiveButtonIndex);

	// Moves the active button index through the menu. Value indicates the direction and number of indices to move through the menu. Wrap determines whether the active
	// button index should wrap around to the other end of the list when the navigation value moves it off of the end of the list. For example, if the menu is navigated
	// by -1 when the active index is 0, should the active button index become the index of the last registered button or remain at 0
	void Navigate(int32 Value, bool Wrap);

	void PressActiveButton();
	void PressActiveButtonIfUnderMouse();
	bool IsActiveButtonUnderMouse() const;

private:
	void ActivateButton(int32 ButtonIndex);
	void DeactivateButton(int32 ButtonIndex);
	void SetActiveButtonIndex(int32 NewActiveButtonIndex);
	TObjectPtr<UProject1ButtonWidgetBase> GetActiveButton() const;

	UFUNCTION()
	void OnMouseEnteredRegisteredButtonGeometry(UProject1ButtonWidgetBase* Button);
};
